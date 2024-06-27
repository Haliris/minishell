/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:21:14 by jteissie          #+#    #+#             */
/*   Updated: 2024/06/06 13:39:20 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	print_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int	print_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
	return (print_strlen(s));
}

void	ft_putnbr_base(unsigned int number, char *base, int *print)
{
	unsigned int	base_len;

	base_len = 0;
	while (base[base_len])
		base_len++;
	if (number >= base_len)
	{
		ft_putnbr_base(number / base_len, base, print);
		ft_putchar_fd(base[number % base_len], 1);
		*print = *print + 1;
		return ;
	}
	ft_putchar_fd(base[number], 1);
	*print = *print + 1;
	return ;
}

void	ft_putptr(unsigned long ptr, int *print)
{
	char	*hexa;

	hexa = "0123456789abcdef";
	if (ptr >= 16)
	{
		ft_putptr(ptr / 16, print);
		ft_putchar_fd(hexa[ptr % 16], 1);
		*print = *print + 1;
		return ;
	}
	ft_putchar_fd(hexa[ptr], 1);
	*print = *print + 1;
	return ;
}
