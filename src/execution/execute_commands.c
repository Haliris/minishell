/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:19:59 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/14 11:22:32 by jteissie         ###   ########.fr       */
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

int	count_commands(t_parser *data)
{
	t_lex_parser	*roaming;
	int				cmd_count;

	roaming = data->node;
	cmd_count = 0;
	while (roaming)
	{
		if (roaming->type == TK_PARS_CMD)
		{
			cmd_count++;
		}
		roaming = roaming->next;
	}
	return (cmd_count);
}

int	execute_commands(t_parser *data, char **envp)
{
	int				cmd_count;
	t_lex_parser	*roaming;
	int				i;

	cmd_count = count_commands(data);
	i = cmd_count;
	roaming = data->node;
	while (roaming && i)
	{
		if (roaming->type == TK_PARS_CMD)
		{
			if (process_command(roaming, envp, cmd_count - i, data) == PANIC)
				return (PANIC);
			i--;
		}
		roaming = roaming->next;
	}
	wait_for_children(cmd_count);
	return (EXIT_SUCCESS);
}

int	execute_data(t_parser *parsed_data, char **env)
{
	int	status;

	status = SUCCESS;
	if (parsed_data->node)
		status = execute_commands(parsed_data, env);
	if (parsed_data->node)
		free_parsed_mem(parsed_data);
	return (status);
}
