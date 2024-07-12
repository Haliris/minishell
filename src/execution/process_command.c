/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:07:11 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/12 19:24:12 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cmd(char *cmd, char **env)
{
	char	**command;
	char	*exec_path;

	command = ft_split(cmd, ' ');
	if (!command || !command[0])
	{
		if (command)
			trash(command);
		handle_error("Command split error", EXIT_FAILURE);
	}
	if (access(command[0], F_OK | X_OK) == 0)
	{
		exec_path = command[0];
		if (execve(exec_path, command, env) == -1)
		{
			trash(command);
			handle_error(strerror(errno), errno);
		}
	}
}

void	check_pipes(t_lex_parser *table, int pipe_status[])
{
	t_lex_parser	*roaming;

	roaming = table;
	while (roaming->prev && roaming->prev->type != TK_PARS_PIPE)
		roaming = roaming->prev;
	if (roaming->prev && roaming->prev->type == TK_PARS_PIPE)
		pipe_status[0] = TRUE;
	while (roaming->next && roaming->next->type != TK_PARS_PIPE)
		roaming = roaming->next;
	if (roaming->next && roaming->next->type == TK_PARS_PIPE)
		pipe_status[1] = TRUE;
}

int	open_pipes(t_lex_parser *parsed, int p_fd[])
{
	int	has_pipe[2];

	has_pipe[0] = FALSE;
	has_pipe[1] = FALSE;
	check_pipes(parsed, has_pipe);
	if (pipe(p_fd) < 0)
		return (-1);
	if (has_pipe[0] == FALSE)
	{
		close(p_fd[0]);
		p_fd[0] = 0;
	}
	if (has_pipe[1] == FALSE)
	{
		close(p_fd[1]);
		p_fd[1] = 0;
	}
	return (SUCCESS);
}

int	redirect_parent(int p_fd[], int file_fd[])
{
	int	dup_status;

	dup_status = 0;
	if (p_fd[0])
		dup_status += dup2(p_fd[0], STDIN_FILENO);
	if (file_fd[0])
		close(file_fd[0]);
	if (file_fd[1])
		close(file_fd[1]);
	close(p_fd[0]);
	close(p_fd[1]);
	return (dup_status);
}

int	process_command(t_lex_parser *parsed, char **envp)
{
	int			pipe_fd[2];
	int			file_fd[2];
	t_cmd_table	*cmd_table;
	pid_t		pid_child;

	cmd_table = parsed->table;
	if (open_files(file_fd, parsed) == -1 || open_pipes(parsed, pipe_fd) == -1)
		return (PANIC);
	pid_child = fork();
	if (pid_child < 0)
		return (PANIC);
	if (pid_child == 0)
	{
		if (redirect_child(file_fd, pipe_fd) == PANIC)
			handle_error("syscall error in exec child.\n", errno);
		execute_cmd(cmd_table->cmd, envp);
	}
	else
	{
		parsed->type = TK_PARS_RESERVED;
		if (redirect_parent(pipe_fd, file_fd) < 0)
			return (PANIC);
	}
	return (SUCCESS);
}
