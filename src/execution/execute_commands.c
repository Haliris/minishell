/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:19:59 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/29 12:00:11 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_for_children(t_data *data)
{
	int			status;
	t_pid_data	*roaming;
	int			error_code;

	error_code = SIG_OFFSET;
	status = 0;
	roaming = data->piddata;
	while (roaming)
	{
		waitpid(roaming->pid, &status, 0);
		roaming = roaming->next;
	}
	if (WIFSIGNALED(status))
		error_code += WTERMSIG(status);
	else
		error_code = WEXITSTATUS(status);
	data->errcode = error_code;
}

int	count_commands(t_parser *data)
{
	t_parser	*roaming;
	int			cmd_count;

	roaming = data;
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

int	execute_commands(t_data *data)
{
	int				cmd_count;
	int				index;
	t_parser		*roaming;
	t_cmd_table		*cmd_table;

	cmd_count = count_commands(data->parsedata);
	index = cmd_count;
	roaming = data->parsedata;
	while (roaming && index)
	{
		if (roaming->type == TK_PARS_CMD)
		{
			cmd_table = roaming->table;
			if (cmd_count == 1 && is_builtin(cmd_table->cmd_buff->buffer, 0))
				execute_builtin(cmd_table->cmd_buff, data, PARENT, 0);
			else if (process_command(roaming, data) == PANIC)
				return (PANIC);
			index--;
		}
		if (data->parsedata)
			roaming = roaming->next;
	}
	wait_for_children(data);
	return (EXIT_SUCCESS);
}

int	execute_data(t_data *data)
{
	int			status;

	status = SUCCESS;
	data->std_fd[0] = dup(STDIN_FILENO);
	data->std_fd[1] = dup(STDOUT_FILENO);
	if (data->std_fd[0] < 0 || data->std_fd[1] < 0)
		return (PANIC);
	if (data->parsedata->table)
		status = execute_commands(data);
	if (data->parsedata)
		free_parsed_mem(&data->parsedata);
	close(data->std_fd[0]);
	close(data->std_fd[1]);
	if (data->prev_fd != STDIN_FILENO)
		close(data->prev_fd);
	if (data->piddata)
		free_piddata(data);
	data->piddata = NULL;
	data->prev_fd = STDIN_FILENO;
	return (status);
}
