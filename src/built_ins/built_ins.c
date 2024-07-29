/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:59:53 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/29 22:47:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	reset_terminal(t_data *data)
{
	int	dup_status;

	dup_status = 0;
	dup_status += dup2(data->std_fd[0], STDIN_FILENO);
	dup_status += dup2(data->std_fd[1], STDOUT_FILENO);
	if (dup_status < 0)
		return (PANIC);
	return (SUCCESS);
}

static void	read_and_discard_pipein(int pipe[])
{
	char	buffer[1024];
	int		status;

	if (!pipe[0])
		return ;
	status = 1;
	while (status > 0)
		status = read(STDIN_FILENO, &buffer, sizeof(buffer));
}

void	call_builtin(char **command, t_data *data, int mode, int pipe[])
{
	if (mode == CHILD)
		read_and_discard_pipein(pipe);
	if (ft_strcmp(command[0], "echo") == 0)
		call_echo(command);
	else if (ft_strcmp(command[0], "cd") == 0)
		call_cd(data, command);
	else if (ft_strcmp(command[0], "pwd") == 0)
		call_pwd();
	else if (ft_strcmp(command[0], "exit") == 0)
	{
		if (mode == PARENT)
		{
			close(data->std_fd[0]);
			close(data->std_fd[1]);
		}
		call_exit(data, command, mode);
	}
	else if (ft_strcmp(command[0], "export") == 0)
		call_export(data, command);
	else if (ft_strcmp(command[0], "env") == 0)
		call_env(data, command);
	else if (ft_strcmp(command[0], "unset") == 0)
		call_unset(data, command);
}

static int	builtin_redir_parent(char **command, t_data *data)
{
	if (process_files(data->parsedata) < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		free_strarray(command);
		return (PANIC);
	}
	return (SUCCESS);
}

void	execute_builtin(t_vector *vector, t_data *data, int mode, int pipe[])
{
	char	**command;

	command = make_command_array(vector);
	if (mode == PARENT)
	{
		if (builtin_redir_parent(command, data) == PANIC)
			return ;
	}
	free_parsed_mem(&data->parsedata);
	free(data->parsedata);
	if (!command || !command[0])
	{
		if (command)
			free_strarray(command);
		if (mode == CHILD)
			handle_error("Built_in split error", EXIT_FAILURE, data, NULL);
		else
			return ;
	}
	call_builtin(command, data, mode, pipe);
	if (command)
		free_strarray(command);
	if (mode == PARENT && reset_terminal(data) == PANIC)
		return ;
}
