/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_executables.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:08:45 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/25 16:00:16 by marvin           ###   ########.fr       */
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

t_token	*get_exec_tk(t_data *data, char *input, size_t start_idx)
{
	char	*cmd;
	char	*exec_path;

	cmd = get_substr(input, start_idx);
	if (!cmd)
		return (NULL);
	if (access(cmd, X_OK) != -1)
		return (get_token(data, cmd, ft_strdup(cmd), TK_EXECUTABLE));
	exec_path = get_exec_path(data, input, start_idx);
	if (!exec_path)
	{
		free(cmd);
		return (get_token(data, NULL, NULL, TK_INVALID));
	}
	return (get_token(data, cmd, exec_path, TK_EXECUTABLE));
}
