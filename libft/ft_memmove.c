/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:35:42 by jteissie          #+#    #+#             */
/*   Updated: 2024/05/20 10:58:00 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*backward_copy(char *to, const char *from, size_t index)
{
	while (index > 0)
	{
		to[index - 1] = from[index - 1];
		index--;
	}
	to[index] = from[index];
	return (to);
}

static char	*normal_copy(char *to, const char *from, size_t index, size_t n)
{
	while (index < n)
	{
		to[index] = from[index];
		index++;
	}
	return (to);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	const char		*from;
	char			*to;

	if ((dest == NULL && src == NULL) || n == 0)
		return (dest);
	from = src;
	to = dest;
	if (to > from)
	{
		i = n;
		to = backward_copy(to, from, i);
	}
	else
	{
		i = 0;
		to = normal_copy(to, from, i, n);
	}
	return (dest);
}
