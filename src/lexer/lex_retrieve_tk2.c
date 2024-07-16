/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_retrieve_tk2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:38:30 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/16 10:50:35 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*get_redir_tk(t_data *data, char *input, size_t start_idx)
{
	char	*lexstr;

	lexstr = NULL;
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

	search_str = get_substr(input, start_idx);
	if (!search_str)
		return (NULL);
	search_str++;
	path = get_varval(data->env_vars, search_str);
	search_str--;
	return (get_token(data, search_str, path, TK_PATH));
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
	token = get_token(data, ft_substr(input, start_idx, limit_end - start_idx),
			NULL, TK_HEREDOC);
	if (!token)
		return (free(limiter), NULL);
	token->heredoc = process_here_doc(limiter);
	free(limiter);
	return (token);
}
