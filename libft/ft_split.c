/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 17:14:10 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/23 15:26:31 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_sep(char c, char sep, int quotes)
{
	if (c != '\0' && quotes)
		return (0);
	if (c == sep || c == '\0')
		return (1);
	return (0);
}

static int	count_words(char const *str, char sep)
{
	int	i;
	int	words;
	int	quotes;

	i = 0;
	quotes = 0;
	words = 0;
	if (!str || str[0] == '\0')
		return (0);
	if (check_sep(str[i], sep, quotes))
		i++;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && !quotes)
		{
			quotes = 1;
			i++;
		}
		else if ((str[i] == '\'' || str[i] == '\"') && quotes)
		{
			quotes = 0;
			i++;
		}
		if (check_sep(str[i], sep, quotes)
			&& !check_sep(str[i - 1], sep, quotes))
			words++;
		i++;
	}
	if (check_sep(str[i], sep, quotes) && !check_sep(str[i - 1], sep, quotes))
		words++;
	return (words);
}

static char	*build_str(char const *str, int index, int word_index)
{
	char	*split_str;
	int		i;

	i = 0;
	split_str = ft_calloc(word_index + 1, sizeof(char));
	if (!split_str)
		return (NULL);
	while (word_index > 0)
	{
		split_str[i] = str[index - word_index];
		i++;
		word_index--;
	}
	split_str[i] = '\0';
	return (split_str);
}

static char	**assemble(char **split, char const *s, char c, int slots)
{
	int	i;
	int	word_index;
	int	split_index;
	int	quotes;

	i = 0;
	word_index = 0;
	split_index = 0;
	quotes = 0;
	while (split_index < slots && s && s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			quotes = 1;
			i++;
		}
		else if ((s[i] == '\'' || s[i] == '\"') && quotes)
		{
			quotes = 0;
			i++;
		}
		while (!check_sep(s[i], c, quotes))
		{
			word_index++;
			i++;
		}
		if (check_sep(s[i], c, quotes) && !check_sep(s[i - 1], c, quotes))
		{
			split[split_index] = build_str(s, i, word_index);
			split_index++;
			word_index = 0;
		}
		i++;
	}
	split[split_index] = NULL;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		words;
	int		safety_check;

	words = 0;
	words = count_words(s, c);
	split = ft_calloc(words + 1, sizeof(char *));
	if (!split)
		return (NULL);
	split = assemble(split, s, c, words);
	safety_check = 0;
	while (split[safety_check])
		safety_check++;
	if (safety_check < words)
	{
		safety_check = 0;
		while (safety_check <= words)
		{
			free(split[safety_check]);
			safety_check++;
		}
		free(split);
		return (NULL);
	}
	return (split);
}
