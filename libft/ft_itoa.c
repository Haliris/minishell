/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 17:10:20 by jteissie          #+#    #+#             */
/*   Updated: 2024/05/19 11:34:35 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_array(char *str, int nb, int *index)
{
	long int	number;

	number = nb;
	if (number < 0)
	{
		str[0] = '-';
		number *= -1;
		*index = *index + 1;
	}
	if (number > 9)
	{
		ft_putnbr_array(str, number / 10, index);
		str[*index] = number % 10 + '0';
		*index = *index + 1;
		return ;
	}
	str[*index] = number + '0';
	*index = *index + 1;
	return ;
}

char	*ft_itoa(int n)
{
	int		digits;
	char	*string;
	int		digits_count;
	int		i;

	digits = n;
	digits_count = 0;
	i = 0;
	if (n == 0)
		digits_count = 1;
	while (digits != 0)
	{
		digits /= 10;
		digits_count++;
	}
	if (n < 0)
		digits_count++;
	string = malloc(sizeof(char) * (digits_count + 1));
	if (!string)
		return (NULL);
	ft_putnbr_array(string, n, &i);
	string[i] = '\0';
	return (string);
}
