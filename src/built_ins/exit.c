/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:27:00 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/16 21:31:48 by marvin           ###   ########.fr       */
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
		if (str[index] > 0 || str[index] < 9)
			return (TRUE);
		index++;
	}
	return (FALSE);
}

void	call_exit(char **cmd)
{
	int	exit_code;

	if (!cmd || !cmd[1])
	{
		trash(cmd);
		exit(EXIT_SUCCESS);
	}
	exit_code = EXIT_FAILURE;
	if (cmd[2] != NULL)
	{
		trash(cmd);
		return ; // Error in trying to exit lmfao, check bash
	}
	if (is_not_number(cmd[1]) == TRUE)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	}
	else
		exit_code = ft_atoi(cmd[1]);
	trash(cmd);
	exit(exit_code);
}
