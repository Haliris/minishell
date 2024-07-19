/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:52:36 by bento             #+#    #+#             */
/*   Updated: 2024/07/19 11:52:57 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

bool	is_delim(char c)
{
	return (in(c, "$ \t\n\v\f\r=()<>|"));
}

void	replace_str(char **old, char *new)
{
	if (!old || !*old)
		return ;
	free(*old);
	*old = new;
}

char	*get_substr(char *input, size_t start_idx)
{
	char	*substr;
	size_t	i;

	i = start_idx;
	while (input[i] && !is_space(input[i]) && !in(input[i], "$()|<>=\"\'"))
		i++;
	substr = ft_substr(input, start_idx, i - start_idx);
	if (!substr)
		return (NULL);
	return (substr);
}

bool	var_in_str(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i + 1])
	{
		if (str[i] == '$' && str[i + 1] && !in(str[i + 1], "$=()\"\' \t\n\v\f\r"))
			return (true);
		i++;
	}
	return (false);
}

int	count_str_vars(char *str)
{
	int		count;
	size_t	i;

	count = 0;
	i = 0;
	while (str && str[i])
	{
		if (str[i] == '$' && str[i + 1] && !in(str[i + 1], "$=()\"\' \t\n\v\f\r"))
			count++;
		i++;
	}
	return (count);
}
