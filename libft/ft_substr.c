/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 17:37:49 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/26 13:04:03 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*sub_str;
	unsigned int		i;

	i = 0;
	if (s && len > ft_strlen(s))
		len = ft_strlen(s);
	if (s && start >= ft_strlen(s))
		len = 0;
	if (s && start < ft_strlen(s) && len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	sub_str = (char *)malloc(sizeof(char) * len + 1);
	if (!sub_str)
		return (NULL);
	if (start < ft_strlen(s))
	{
		while (s[start] && i < len)
		{
			sub_str[i] = s[start];
			start++;
			i++;
		}
	}
	sub_str[i] = '\0';
	return (sub_str);
}
