/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:27:00 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/22 14:03:52 by jteissie         ###   ########.fr       */
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
	free_strarray(cmd);
}

static int	check_overflow(char *str)
{
	if (ft_strlen(str) > 11)
		return (TRUE);
	return (FALSE);
}

void	call_exit(t_data *data, char **cmd, int mode)
{
	int	exit_code;

	(void)data;
	exit_code = EXIT_FAILURE;
	if (!cmd[1] || cmd[2])
	{
		free_strarray(cmd);
		if (mode == PARENT && !cmd[1])
			ft_putstr_fd("exit\n", STDOUT_FILENO);
		else if (cmd[1] && cmd[2])
			ft_putstr_fd("minishell: exit: too may arguments\n", STDERR_FILENO);
		exit(clean_exit(data, EXIT_FAILURE));
	}
	if (is_not_number(cmd[1]) == TRUE || check_overflow(cmd[1]))
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
