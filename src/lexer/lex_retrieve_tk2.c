/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_retrieve_tk2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:38:30 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/11 14:38:30 by bthomas          ###   ########.fr       */
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
		{
			lexstr = ft_strdup("<<");
			return (get_token(data, lexstr, NULL, TK_HEREDOC));
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
	path = get_env_var(search_str);
	search_str--;
	return (get_token(data, search_str, path, TK_PATH));
}
