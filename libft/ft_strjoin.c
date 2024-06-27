/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 17:35:02 by jteissie          #+#    #+#             */
/*   Updated: 2024/03/24 17:24:10 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	int		i;
	int		parse_index;

	i = 0;
	parse_index = 0;
	joined = malloc (sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!joined)
		return (NULL);
	while (s1[parse_index])
	{
		joined[i] = s1[parse_index];
		i++;
		parse_index++;
	}
	parse_index = 0;
	while (s2[parse_index])
	{
		joined[i] = s2[parse_index];
		i++;
		parse_index++;
	}
	joined[i] = '\0';
	return (joined);
}
