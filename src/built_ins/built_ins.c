/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:59:53 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/16 18:03:36 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	call_builtin(char **command, char **env)
{
	(void)env;

	if (ft_strcmp(command[0], "echo") == 0)
		call_echo(command);
	// if (ft_strcmp(command[0], "cd") == 0)
	// 	call_cd();
	// if (ft_strcmp(command[0], "pwd") == 0)
	// 	call_pwd();
	// if (ft_strcmp(command[0], "export") == 0)
	// 	call_export();
	// if (ft_strcmp(command[0], "unset") == 0)
	// 	call_unset();
	// if (ft_strcmp(command[0], "env") == 0)
	// 	call_env();
	// if (ft_strcmp(command[0], "exit") == 0)
	// 	call_exit();
}

void	execute_builtin(char *cmd, char **env, t_parser *data)
{
	char **command;

	command = ft_split(cmd, " ");
	free_parsed_mem(data);
	if (!command || !command[0])
	{
		if (command)
			trash(command);
		handle_error("Command split error", EXIT_FAILURE);
	}
	call_builtin(command, env);
}
