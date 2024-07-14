/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 16:35:10 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/14 13:25:51 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	s1len;
	size_t	s2len;

	if (!s1 && !s2)
		return (0);
	else if (!s1 || !s2)
		return (1);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	if (s1len != s2len)
		return (1);
	return (ft_strncmp(s1, s2, s1len));
}
