/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarrjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:32:23 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/29 11:40:58 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	total_len(char **arr, size_t num_entries)
{
	size_t	len;
	size_t	i;

	if (!arr || !*arr)
		return (0);
	len = 0;
	i = 0;
	while (i < num_entries && arr[i])
	{
		len += ft_strlen(arr[i]);
		i++;
	}
	return (len);
}

char	*ft_strarrjoin(char **arr, size_t num_entries)
{
	char	*ret;
	size_t	ret_len;
	size_t	i;

	ret_len = total_len(arr, num_entries);
	if (!ret_len)
		return (NULL);
	ret = (char *)ft_calloc(ret_len + 1, 1);
	if (!ret)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		ft_strlcat(ret, arr[i], ft_strlen(arr[i]));
		i++;
	}
	return (ret);
}
