/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:52:36 by bento             #+#    #+#             */
/*   Updated: 2024/07/27 17:10:52 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	replace_str(char **old, char *new)
{
	if (!old || !*old)
		return ;
	if (*old)
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

/* problem chars: & | < > ; ( ) \ " '
	but, bash allows them */
void	remove_lim_node(t_token *node)
{
	if (node->prev && node->next)
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	else if (node->prev)
		node->prev->next = node->next;
	else if (node->next)
		node->next->prev = node->prev;
	if (node->lexstr)
		free(node->lexstr);
	free(node);
}
