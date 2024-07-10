/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_bools1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:50:09 by bento             #+#    #+#             */
/*   Updated: 2024/07/10 13:50:50 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/* e.g., '' or  "" , we can ignore them */
bool	empty_quote(char *input, size_t start_idx)
{
	char	quote;

	if (input[start_idx] != '\'' && input[start_idx] != '\"')
		return (false);
	quote = input[start_idx];
	if (input[start_idx + 1] == quote)
		return (true);
	return (false);
}

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

/* Not sure if I'll use the below or not */
bool	is_builtin(char *input, size_t start_idx)
{
	char	*lexstr;
	bool	ret;

	ret = false;
	lexstr = get_substr(input, start_idx);
	if (!lexstr)
		return (ret);
	if (ft_strncmp(lexstr, "echo", 4) == 0)
		ret = true;
	else if (ft_strncmp(lexstr, "cd", 2) == 0)
		ret = true;
	else if (ft_strncmp(lexstr, "pwd", 3) == 0)
		ret = true;
	else if (ft_strncmp(lexstr, "export", 6) == 0)
		ret = true;
	else if (ft_strncmp(lexstr, "unset", 5) == 0)
		ret = true;
	else if (ft_strncmp(lexstr, "env", 3) == 0)
		ret = true;
	else if (ft_strncmp(lexstr, "exit", 4) == 0)
		ret = true;
	free(lexstr);
	return (ret);
}
