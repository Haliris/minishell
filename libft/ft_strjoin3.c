/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:31:28 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/26 14:14:56 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*result;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	if (!len)
		return (ft_strdup(""));
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, len + 1);
	ft_strlcat(result, s2, len + 1);
	ft_strlcat(result, s3, len + 1);
	return (result);
}
