/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_retrieve_tk.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:38:30 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/27 17:07:13 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*get_redir_tk(t_data *data, char *input, size_t start_idx)
{
	char	*lexstr;

	lexstr = NULL;
	if (get_last_tk_type(data) == TK_REDIR)
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
t_token	*get_var_tk(t_data *data, char *input, size_t start_idx)
{
	char	*search_str;
	char	*path;
	size_t	end_idx;

	search_str = NULL;
	if (input[start_idx] == '$' && input[start_idx + 1] == '$')
		search_str = ft_strdup("$$");
	end_idx = start_idx + 1;
	if (!search_str && !ft_isalpha(input[end_idx]) && input[end_idx] != '_' )
		return (NULL);
	while (input[end_idx] && !is_delim(input[end_idx])
		&& !invalid_path_char(input[end_idx]))
		end_idx++;
	if (end_idx == start_idx + 1 && !search_str)
		return (NULL);
	if (!search_str)
		search_str = ft_substr(input, start_idx, end_idx - start_idx);
	if (!search_str)
		return (NULL);
	search_str++;
	path = get_varval(data->env_vars, search_str);
	search_str--;
	return (get_token(data, search_str, path, TK_PATH));
}

int	get_heredoc_tk(t_token *roaming, t_data *data)
{
	char	*limiter;

	limiter = ft_strdup(roaming->next->lexstr);
	if (!limiter)
	{
		roaming->type = TK_INVALID;
		return (PANIC);
	}
	remove_lim_node(roaming->next);
	roaming->type = TK_HEREDOC;
	roaming->heredoc = process_here_doc(limiter, data);
	free(limiter);
	if (!roaming->heredoc)
		return (PANIC);
	return (SUCCESS);
}
