/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:27:00 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/16 19:38:18 by jteissie         ###   ########.fr       */
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
		if (str[index] < 0 || str[index] > 9)
			return (FALSE);
		index++;
	}
	return (SUCCESS);
}

void	call_exit(char **cmd)
{
	int	exit_code;

	if (cmd[2] != NULL)
	{
		trash(cmd);
		return ; // Error in trying to exit lmfao, check bash
	}
	if (is_not_number(cmd[1]) == TRUE)
	{
		trash(cmd);
		ft_printf("exit: %s: numeric argument required\n", cmd[1]);
		return ;
	}
	exit_code = ft_atoi(cmd[1]);
	trash(cmd);
	exit(exit_code);
}
