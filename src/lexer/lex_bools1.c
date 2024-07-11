/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_bools1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:50:09 by bento             #+#    #+#             */
/*   Updated: 2024/07/11 09:44:03 by bthomas          ###   ########.fr       */
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

bool	is_executable(char *input, size_t start_idx)
{
	char	*cmd;
	char	*substr;
	bool	retval;
	int		access_code;

	substr = get_substr(input, start_idx);
	if (substr)
	{
		access_code = access(substr, X_OK);
		free(substr);
		if (access_code != -1)
			return (true);
	}
	cmd = NULL;
	cmd = get_exec_path(input, start_idx);
	if (cmd)
	{
		free(cmd);
		retval = true;
	}
	else
		retval = false;
	return (retval);
}
