/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 17:36:54 by jteissie          #+#    #+#             */
/*   Updated: 2024/05/22 11:10:33 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	little_i;

	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (i < len && big[i])
	{
		little_i = 0;
		while (big[i + little_i] == little[little_i])
		{
			if (i + little_i == len)
				return (NULL);
			little_i++;
			if (little[little_i] == '\0')
				return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}
