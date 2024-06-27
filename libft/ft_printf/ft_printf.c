/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 16:42:23 by jteissie          #+#    #+#             */
/*   Updated: 2024/06/06 13:39:05 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	process_string(const char *str, va_list args)
{
	int	i;
	int	print_count;

	i = 0;
	print_count = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '%')
		{
			print_count += triage_format(str[i + 1], args);
			i++;
		}
		else
		{
			ft_putchar_fd(str[i], 1);
			print_count++;
		}
		i++;
	}
	return (print_count);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	args;
	int		print_count;

	va_start(args, fmt);
	print_count = process_string(fmt, args);
	va_end(args);
	return (print_count);
}
