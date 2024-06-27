/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:38:32 by jteissie          #+#    #+#             */
/*   Updated: 2024/05/18 17:07:13 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_len;
	size_t	total_len;

	i = 0;
	if ((!dest) && size == 0)
		return (ft_strlen(src));
	dest_len = ft_strlen(dest);
	total_len = ft_strlen(dest) + ft_strlen(src);
	if (dest_len >= size || size == 0)
		return (ft_strlen(src) + size);
	while (i < size - dest_len - 1 && src[i])
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (total_len);
}
