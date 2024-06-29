/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_bools1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bento <bento@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:50:09 by bento             #+#    #+#             */
/*   Updated: 2024/06/29 20:20:24 by bento            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

bool	is_space(unsigned char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

bool	in(unsigned char c, const char *str)
{
	while (*str)
	{
		if (*str == c)
			return (true);
		str++;
	}
	return (false);
}

bool	is_executable(char *input, size_t start_idx)
{
	char	*lexstr;
	bool	ret;

	ret = false;
	lexstr = get_substr(input, start_idx);
	if (!lexstr)
		return (ret);
	if (access(lexstr, X_OK) != -1)
		ret = true;
	free(lexstr);
	return (ret);
}

bool	is_builtin(char *input, size_t start_idx)
{
	char	*lexstr;
	bool	ret;

	ret = false;
	lexstr = get_substr(input, start_idx);
	if (!lexstr)
		return (ret);
	if (ft_strcmp(lexstr, "echo") == 0)
		ret = true;
	else if (ft_strcmp(lexstr, "cd") == 0)
		ret = true;
	else if (ft_strcmp(lexstr, "pwd") == 0)
		ret = true;
	else if (ft_strcmp(lexstr, "export") == 0)
		ret = true;
	else if (ft_strcmp(lexstr, "unset") == 0)
		ret = true;
	else if (ft_strcmp(lexstr, "env") == 0)
		ret = true;
	else if (ft_strcmp(lexstr, "exit") == 0)
		ret = true;
	free(lexstr);
	return (ret);
}
