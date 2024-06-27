/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_triage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:09:31 by jteissie          #+#    #+#             */
/*   Updated: 2024/06/06 13:39:12 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	triage_format(char f, va_list args)
{
	int	print_count;

	print_count = 0;
	if (f == 'c' || f == 's')
		print_char(args, &print_count, f);
	else if (f == 'u')
		print_unsigned(args, &print_count);
	else if (f == 'p')
		print_ptr(args, &print_count);
	else if (f == 'd' || f == 'i' || f == 'x' || f == 'X')
		print_nbr(args, &print_count, f);
	else if (f == '%')
		print_count = print_putchar_fd('%', 1);
	return (print_count);
}

void	print_unsigned(va_list args, int *count)
{
	unsigned long	u_int;

	u_int = va_arg(args, unsigned int);
	ft_putnbr_base(u_int, "0123456789", count);
}

void	print_nbr(va_list args, int *count, char format)
{
	int	number;

	number = va_arg(args, int);
	if (format == 'd' || format == 'i')
	{
		if (number < 0)
		{
			number *= -1;
			ft_putchar_fd('-', 1);
			*count = *count + 1;
		}
		ft_putnbr_base(number, "0123456789", count);
	}
	if (format == 'x')
		ft_putnbr_base(number, "0123456789abcdef", count);
	if (format == 'X')
		ft_putnbr_base(number, "0123456789ABCDEF", count);
}

void	print_ptr(va_list args, int *count)
{
	unsigned long	cast;

	cast = va_arg(args, unsigned long);
	if (!cast)
	{
		*count = *count + 5;
		ft_putstr_fd("(nil)", 1);
	}
	else
	{
		*count = *count + print_putchar_fd('0', 1);
		*count = *count + print_putchar_fd('x', 1);
		ft_putptr(cast, count);
	}
}

void	print_char(va_list args, int *count, char format)
{
	if (format == 'c')
		*count = *count + print_putchar_fd((char)va_arg(args, int), 1);
	else
		*count = *count + print_putstr_fd(va_arg(args, char *), 1);
}
