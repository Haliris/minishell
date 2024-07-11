/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_retrieve_tk2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:38:30 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/11 08:25:14 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*get_redir_tk(t_data *data, char *input, size_t start_idx)
{
	t_token	*token;
	char	*lexstr;

	if (input[start_idx] == '<')
	{
		if (input[start_idx + 1] == '<')
		{
			lexstr = ft_strdup("<<");
			return (get_token(data, lexstr, TK_HEREDOC));
		}
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
	return (get_token(data, lexstr, TK_REDIR));
}

/* Might need to change this to account for "||" */
t_token	*get_pipe_tk(t_data *data, char *input, size_t start_idx)
{
	return (get_token(data, ft_strdup("|"), TK_PIPE));
}

t_token	*get_path_tk(t_data *data, char *input, size_t start_idx)
{
	char	*search_str;
	char	*path;

	search_str = get_substr(input, start_idx);
	if (!search_str)
		return (NULL);
	search_str++;
	path = get_env_var(search_str);
	free(search_str);
	if (!path)
		return (NULL);
	return (get_token(data, path, TK_PATH));
}
