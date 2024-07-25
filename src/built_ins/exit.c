/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:27:00 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/23 22:07:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_not_number(char *str)
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

static void	exit_error(char **cmd)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(cmd[1], STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	free_strarray(cmd);
}

void	call_exit(t_data *data, char **cmd, int mode)
{
	long	exit_code;

	(void)data;
	exit_code = EXIT_FAILURE;
	if (!cmd[1] || cmd[2])
	{
		if (mode == PARENT && !cmd[1])
			ft_putstr_fd("exit\n", STDOUT_FILENO);
		else if (cmd[1] && cmd[2])
			ft_putstr_fd("minishell: exit: too may arguments\n", STDERR_FILENO);
		free_strarray(cmd);
		exit(clean_exit(data, EXIT_FAILURE));
	}
	if (is_not_number(cmd[1]) == TRUE)
	{
		exit_error(cmd);
		exit(clean_exit(data, EXIT_FAILURE));
	}
	exit_code = ft_atoi(cmd[1]);
	if (mode == PARENT)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	free_strarray(cmd);
	exit(clean_exit(data, exit_code));
}
