/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:59:53 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/17 13:42:30 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define FD_STDIN 3
#define FD_STDOUT 4

void	call_builtin(char **command, char **env, int mode)
{
	(void)env;

	if (ft_strcmp(command[0], "echo") == 0)
		call_echo(command);
	else if (ft_strcmp(command[0], "cd") == 0)
		call_cd(command);
	else if (ft_strcmp(command[0], "pwd") == 0)
		call_pwd(command);
	// else if (ft_strcmp(command[0], "export") == 0)
	// 	call_export();
	// else if (ft_strcmp(command[0], "unset") == 0)
	// 	call_unset();
	// else if (ft_strcmp(command[0], "env") == 0)
	// 	call_env();
	else if (ft_strcmp(command[0], "exit") == 0)
	{
		if (mode == PARENT)
		{
			close(FD_STDIN);
			close(FD_STDOUT);
		}
		call_exit(command);
	}
}

void	execute_builtin(char *cmd, char **env, t_parser *data, int mode)
{
	char **command;

	command = ft_split(cmd, ' ');
	free_parsed_mem(data);
	if (!command || !command[0])
	{
		if (command)
			trash(command);
		if (mode == CHILD)
			handle_error("Command split error", EXIT_FAILURE);
		else
			return ;
	}
	call_builtin(command, env, mode);
}

#undef FD_STDIN
#undef FT_STDOUT
