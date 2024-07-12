/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:44:43 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/12 13:21:08 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	try_absolute_path(char **command, char **env)
{
	char	*exec_path;

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

void	execute(char *av, char **env)
{
	char	**command;
	char	*exec_path;

	command = ft_split(av, ' ');
	if (!command || !command[0])
	{
		if (command)
			trash(command);
		handle_error("Command split error", EXIT_FAILURE);
	}
	try_absolute_path(command, env);
	exec_path = get_execpath(env, command[0]);
	if (!exec_path)
	{
		trash(command);
		handle_error("Command not found", PATH_ERROR);
	}
	if (execve(exec_path, command, env) == -1)
	{
		free(exec_path);
		trash(command);
		handle_error(strerror(errno), errno);
	}
}
