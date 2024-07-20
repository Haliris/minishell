/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:52:36 by bento             #+#    #+#             */
/*   Updated: 2024/07/20 15:43:16 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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
	while (input[i] && !is_delim(input[i]))
		i++;
	if (i == start_idx)
		return (NULL);
	substr = ft_substr(input, start_idx, i - start_idx);
	if (!substr)
		return (NULL);
	return (substr);
}

int	count_str_vars(char *str)
{
	int		count;
	size_t	i;

	count = 0;
	i = 0;
	while (str && str[i])
	{
		if (str[i] == '$' && str[i + 1] && !is_delim(str[i + 1]))
			count++;
		i++;
	}
	return (count);
}

size_t	get_str_tk_len(char *input, size_t startidx)
{
	size_t	len;
	bool	in_quote;
	char	quote;

	len = 0;
	in_quote = false;
	quote = input[startidx];
	while (input[startidx])
	{
		if (!in_quote && in(input[startidx], "\'\""))
		{
			in_quote = true;
			quote = input[startidx];
		}
		else if (in_quote && input[startidx] == quote)
			in_quote = false;
		else if (!in_quote && is_delim(input[startidx]))
			break ;
		else
			len++;
		startidx++;
	}
	return (len);
}
