/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:07:11 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/28 15:19:37 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cmd(t_vector *cmd_vector, t_data *data)
{
	char	**command;
	char	**env;

	command = make_command_array(cmd_vector);
	if (!command || !command[0])
	{
		if (command)
			free_strarray(command);
		handle_error("127: command not found", PATH_ERROR, data, NULL);
	}
	env = build_env(data->env_vars);
	if (access(command[0], F_OK) != 0)
		data->errcode = NOT_FOUND;
	else if (access(command[0], X_OK) != 0)
		data->errcode = CANNOT_EXECUTE;
	else
		execve(command[0], command, env);
	free_strarray(env);
	handle_error(strerror(errno), data->errcode, data, command);
}

int	open_pipes(t_parser *parsed, int p_fd[], int has_pipe[])
{
	check_pipes(parsed, has_pipe);
	p_fd[0] = -1;
	p_fd[1] = -1;
	if (has_pipe[1] == TRUE)
	{
		if (pipe(p_fd) < 0)
			return (-1);
	}
	return (SUCCESS);
}

void	execute_child(t_vector *cmd_vector, t_data *data, int has_pipe[])
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (is_builtin(cmd_vector->buffer, 0))
		execute_builtin(cmd_vector, data, CHILD, has_pipe);
	else
		execute_cmd(cmd_vector, data);
	exit(clean_exit(data, data->errcode));
}

int	handle_parent(t_data *data, pid_t pid_child, int pipe_fd[], int has_pipe[])
{
	if (add_pid_node(data, pid_child) == PANIC
		|| redirect_parent(pipe_fd, has_pipe) == PANIC)
		return (PANIC);
	return (SUCCESS);
}

int	process_command(t_parser *p, t_data *data)
{
	int			pipe_fd[2];
	int			has_pipe[2];
	t_cmd_table	*cmd_table;
	pid_t		pid_child;

	cmd_table = p->table;
	has_pipe[0] = FALSE;
	has_pipe[1] = FALSE;
	if (open_pipes(p, pipe_fd, has_pipe) == -1)
		return (PANIC);
	signal(SIGINT, interrupt_exec);
	signal(SIGQUIT, quit_exec);
	pid_child = fork();
	if (pid_child < 0)
		return (PANIC);
	if (pid_child == 0)
	{
		if (redir_child(p, data, pipe_fd, has_pipe) == PANIC)
			handle_error(strerror(errno), errno, data, NULL);
		execute_child(cmd_table->cmd_buff, data, has_pipe);
	}
	else
		return (handle_parent(data, pid_child, pipe_fd, has_pipe));
	return (SUCCESS);
}
