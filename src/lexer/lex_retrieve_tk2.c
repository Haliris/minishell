/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_retrieve_tk2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:38:30 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/19 15:09:34 by marvin           ###   ########.fr       */
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
			return (get_heredoc_tk(data, input, start_idx));
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

static int	is_operator(char *limiter)
{
	if (ft_strcmp(limiter, "<") == 0)
		return (TRUE);
	if (ft_strcmp(limiter, ">") == 0)
		return (TRUE);
	if (ft_strcmp(limiter, "<<") == 0)
		return (TRUE);
	if (ft_strcmp(limiter, ">>") == 0)
		return (TRUE);
	if (ft_strcmp(limiter, "|") == 0)
		return (TRUE);
	return (FALSE);
}

/* problem chars: & | < > ; ( ) \ " ' 
	but, bash allows them */
t_token	*get_heredoc_tk(t_data *data, char *input, size_t start_idx)
{
	char	*limiter;
	size_t	limit_start;
	size_t	limit_end;
	t_token	*token;

	limit_start = start_idx + 2;
	while (is_space(input[limit_start]))
		limit_start++;
	limit_end = limit_start;
	while (input[limit_end] && !is_space(input[limit_end]))
		limit_end++;
	if (limit_end == limit_start) 
		return (NULL);
	limiter = ft_substr(input, limit_start, limit_end - limit_start);
	if (!limiter)
		return (NULL);
	if (is_operator(limiter))
		return (free(limiter), NULL);
	token = get_token(data, ft_substr(input, start_idx, limit_end - start_idx),
			NULL, TK_HEREDOC);
	if (!token)
		return (free(limiter), NULL);
	token->heredoc = process_here_doc(limiter);
	free(limiter);
	return (token);
}
