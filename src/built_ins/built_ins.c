/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:59:53 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/18 10:05:31 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define FD_STDIN 3
#define FD_STDOUT 4

void	call_builtin(char **command, t_data *data, int mode)
{
	if (ft_strcmp(command[0], "echo") == 0)
		call_echo(data, command);
	else if (ft_strcmp(command[0], "cd") == 0)
		call_cd(data, command);
	else if (ft_strcmp(command[0], "pwd") == 0)
		call_pwd(command);
	else if (ft_strcmp(command[0], "exit") == 0)
	{
		if (mode == PARENT)
		{
			close(FD_STDIN);
			close(FD_STDOUT);
		}
		call_exit(data, command);
	}
	else if (ft_strcmp(command[0], "export") == 0)
		call_export(data, command);
	else if (ft_strcmp(command[0], "env") == 0)
		call_env(data);
}

void	execute_builtin(char *cmd, t_data *data, int mode)
{
	char	**command;

	command = ft_split(cmd, ' ');
	free_parsed_mem(data->parsedata);
	if (!command || !command[0])
	{
		if (command)
			trash(command);
		if (mode == CHILD)
			handle_error("Command split error", EXIT_FAILURE);
		else
			return ;
	}
	call_builtin(command, data, mode);
}

#undef FD_STDIN
#undef FT_STDOUT
