/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:19:59 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/17 18:56:55 by jteissie         ###   ########.fr       */
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
}

int	filter_cmd(t_lex_parser *roaming, char **envp, int std_fds[], t_parser *data)
{
	t_cmd_table		*cmd_table;
	int				cmd_count;

	cmd_count = count_commands(data);
	cmd_table = roaming->table;
	if (cmd_count == 1 && is_builtin(cmd_table->cmd, 0) == TRUE)
	{
		execute_builtin(cmd_table->cmd, envp, data, PARENT);
		return (BUILT_IN);
	}
	else if (process_command(roaming, envp, data, std_fds) == PANIC)
		return (PANIC);
	return (SUCCESS);
}

int	execute_commands(t_parser *data, char **envp, int std_fds[])
{
	int				cmd_count;
	int				index;
	int				status;
	t_lex_parser	*roaming;

	cmd_count = count_commands(data);
	index = cmd_count;
	roaming = data->node;
	status = SUCCESS;
	while (roaming && index)
	{
		if (roaming->type == TK_PARS_CMD)
		{
			status = filter_cmd(roaming, envp, std_fds, data);
			if (status == BUILT_IN || status == PANIC)
				break ;
			index--;
		}
		roaming = roaming->next;
	}
	wait_for_children(cmd_count);
	return (EXIT_SUCCESS);
}

int	execute_data(t_parser *parsed_data, char **env)
{
	int	status;
	int	std_fd[2];
	int	dup_status;

	status = SUCCESS;
	std_fd[0] = dup(STDIN_FILENO);
	std_fd[1] = dup(STDOUT_FILENO);
	dup_status = 0;
	if (std_fd[0] < 0 || std_fd[1] < 0)
		return (PANIC);
	if (parsed_data->node)
		status = execute_commands(parsed_data, env, std_fd);
	if (parsed_data->node)
		free_parsed_mem(parsed_data);
	dup_status += dup2(std_fd[0], STDIN_FILENO);
	dup_status += dup2(std_fd[1], STDOUT_FILENO);
	if (dup_status < 0)
		return (PANIC);
	close(std_fd[0]);
	close(std_fd[1]);
	return (status);
}
