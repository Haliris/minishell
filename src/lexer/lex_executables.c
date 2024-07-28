/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_executables.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:08:45 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/27 17:08:52 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char	*path_join(char *path, char *cmd)
{
	char	*executable;
	char	*temp;

	temp = ft_strjoin(path, "/");
	if (!temp)
		return (NULL);
	executable = ft_strjoin(temp, cmd);
	free(temp);
	if (!executable)
		return (NULL);
	if (access(executable, X_OK) == -1)
	{
		free(executable);
		executable = NULL;
	}
	return (executable);
}

char	*get_exec_path(t_data *data, char *input, size_t start_idx)
{
	char	*cmd;
	char	*path;
	char	**split_path;
	char	*exec_path;
	size_t	i;

	exec_path = NULL;
	cmd = get_substr(input, start_idx);
	if (!cmd)
		return (NULL);
	if (!cmd[0])
		return (free(cmd), NULL);
	path = get_varval(data->env_vars, "PATH");
	if (!path)
		return (free(cmd), NULL);
	split_path = ft_split(path, ':');
	if (!split_path)
		return (free(cmd), free(path), NULL);
	i = -1;
	while (split_path[++i] && !exec_path)
		exec_path = path_join(split_path[i], cmd);
	free_strarray(split_path);
	free(cmd);
	free(path);
	return (exec_path);
}
