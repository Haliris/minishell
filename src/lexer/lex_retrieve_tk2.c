/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_retrieve_tk2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:38:30 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/19 16:14:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_tokentype	check_prev_tk(t_data *data)
{
	t_token	*roaming;

	if (!data->token)
		return (TK_INVALID);
	roaming = data->token;
	while (roaming && roaming->prev)
		roaming = roaming->prev;
	return (roaming->type);
}

t_token	*get_redir_tk(t_data *data, char *input, size_t start_idx)
{
	char	*lexstr;

	lexstr = NULL;
	if (check_prev_tk(data) == TK_REDIR || check_prev_tk(data) == TK_PIPE)
		return (NULL);
	if (input[start_idx] == '<')
	{
		if (input[start_idx + 1] == '<')
			lexstr = ft_strdup("<<");
		else
			lexstr = ft_strdup("<");
	}
	else if (input[start_idx] == '>')
	{
		if (input[start_idx + 1] == '>')
			lexstr = ft_strdup(">>");
		else
			lexstr = ft_strdup(">");
	}
	return (get_token(data, lexstr, NULL, TK_REDIR));
}

/* no null validation for path, because invalid paths are NULL */
t_token	*get_path_tk(t_data *data, char *input, size_t start_idx)
{
	char	*search_str;
	char	*path;
	size_t	end_idx;

	end_idx = start_idx + 1;
	while (input[end_idx] && !is_delim(input[end_idx]))
		end_idx++;
	if (end_idx == start_idx + 1)
		return (NULL);
	search_str = ft_substr(input, start_idx, end_idx - start_idx);
	if (!search_str)
		return (NULL);
	search_str++;
	path = get_varval(data->env_vars, search_str);
	search_str--;
	return (get_token(data, search_str, path, TK_PATH));
}

/* problem chars: & | < > ; ( ) \ " ' 
	but, bash allows them */
static void	remove_lim_node(t_token *node)
{
	if (node->prev && node->next)
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	else if (node->prev)
		node->prev->next = node->next;
	else if (node->next)
		node->next->prev = node->prev;
	if (node->lexstr)
		free(node->lexstr);
	free(node);
}

void	get_heredoc_tk(t_token *roaming, t_data *data)
{
	char	*limiter;

	limiter = ft_strdup(roaming->next->lexstr);
	if (!limiter)
	{
		roaming->type = TK_INVALID;
		return ;
	}
	remove_lim_node(roaming->next);
	roaming->type = TK_HEREDOC;
	roaming->heredoc = process_here_doc(limiter, data);
	free(limiter);
}
