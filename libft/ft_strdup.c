/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:46:49 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/20 17:32:29 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*cpy;

	len = ft_strlen(s);
	if (!len)
		return (NULL);
	cpy = malloc(len + 1);
	if (cpy != NULL)
		ft_strlcpy(cpy, s, len + 1);
	return (cpy);
}
