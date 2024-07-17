/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:27:00 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/17 14:06:24 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_not_number(char *str)
{
	int	index;

	index = 0;
	if (str[index] == '+' || str[index] == '-')
		index++;
	while (str[index])
	{
		if (str[index] < '0' || str[index] > '9')
			return (TRUE);
		index++;
	}
	return (FALSE);
}

void	exit_error(char **cmd)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(cmd[1], STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	trash(cmd);
	exit(EXIT_FAILURE);
}

void	call_exit(char **cmd)
{
	int	exit_code;

	exit_code = EXIT_FAILURE;
	if (!cmd[1])
	{
		trash(cmd);
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	if (cmd[2] != NULL)
	{
		trash(cmd);
		ft_putstr_fd("minishell: exit: too may arguments\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (is_not_number(cmd[1]) == TRUE)
		exit_error(cmd);
	exit_code = ft_atoi(cmd[1]);
	trash(cmd);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(exit_code);
}
