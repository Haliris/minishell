/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:07:11 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/17 14:24:58 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cmd(char *cmd, char **env, t_parser	*data)
{
	char	**command;

	command = ft_split(cmd, ' ');
	free_parsed_mem(data);
	if (!command || !command[0])
	{
		if (command)
			trash(command);
		handle_error("Command split error", EXIT_FAILURE);
	}
	if (access(command[0], F_OK | X_OK) == 0)
	{
		if (execve(command[0], command, env) == -1)
		{
			trash(command);
			handle_error(strerror(errno), errno);
		}
	}
	trash(command);
	handle_error(strerror(errno), errno);
}

int	open_pipes(t_lex_parser *parsed, int p_fd[], int has_pipe[])
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

int	redirect_parent(int p_fd[])
{
	int	dup_status;

	dup_status = 0;
	if (p_fd[0] != -1)
	{
		dup_status += dup2(p_fd[0], STDIN_FILENO);
		close(p_fd[0]);
	}
	if (p_fd[1] != -1)
		close(p_fd[1]);
	return (dup_status);
}

void	execute_child(char *cmd, char **env, t_parser *data)
{
	if (is_builtin(cmd, 0))
		execute_builtin(cmd, env, data, CHILD);
	else
		execute_cmd(cmd, env, data);
	exit(EXIT_SUCCESS);
}

int	process_command(t_lex_parser *p, char **env, t_parser *d, int std_fd[])
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
	pid_child = fork();
	if (pid_child < 0)
		return (PANIC);
	if (pid_child == 0)
	{
		if (redir_child(p, pipe_fd, has_pipe, std_fd) == PANIC)
			handle_error("syscall error in exec child.\n", errno);
		execute_child(cmd_table->cmd, env, d);
	}
	else
	{
		if (redirect_parent(pipe_fd) < 0)
			return (PANIC);
	}
	return (SUCCESS);
}
