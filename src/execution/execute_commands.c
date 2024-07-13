/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:19:59 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/12 15:31:49 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_for_children(int index)
{
	int	status;
	int	error_code;

	error_code = 0;
	status = 0;
	while (index > 0)
	{
		wait(&status);
		if (WEXITSTATUS(status) != 0)
		{
			error_code = WEXITSTATUS(status);
			ft_putstr_fd("Child exited early with error code: ", STDERR_FILENO);
			ft_putnbr_fd(error_code, STDERR_FILENO);
			ft_putchar_fd('\n', STDERR_FILENO);
			ft_putstr_fd(strerror(error_code), STDERR_FILENO);
			ft_putchar_fd('\n', STDERR_FILENO);
		}
		index--;
	}
	if (error_code)
		exit(EXIT_FAILURE);
}

int	execute_commands(t_parser *data, char **envp)
{
	int				cmd_count;
	int				sys_error;
	t_lex_parser	*roaming;
	int				index;

	cmd_count = 0;
	sys_error = FALSE;
	roaming = data->node;
	while (roaming)
	{
		if (roaming->type == TK_PARS_CMD)
		{
			cmd_count++;
		}
		roaming = roaming->next;
	}
	index = cmd_count; 
	roaming = data->node;
	while (roaming && index)
	{
		if (roaming->type == TK_PARS_CMD)
		{
			if (process_command(roaming, envp, cmd_count - index, data) == PANIC)
				{
					sys_error = TRUE;
					break ;
				}
			index--;
		}
		roaming = roaming->next;
	}
	wait_for_children(cmd_count);
	if (sys_error == TRUE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
