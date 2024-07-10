/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_env_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 11:58:51 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/10 11:48:48 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/* Replace this with getenv function */

/* add function to expand out $env vars only when within double quotes. 
replace lexstr */

char	*get_env_var(char *var_str)
{
	char	*path;

	path = getenv(var_str);
	if (!path)
		return (NULL);
	else
		return (ft_strdup(path));
}

bool	is_executable(char *str)
{
	char	exec_path;
	char	*env_path;
	char	**split_path;

	if (access(str, X_OK) != -1)
		return (str);
	env_path = get_env_var("PATH");
	if (!env_path)
		return (false);
	split_path = ft_strsplit(env_path, ':');
	if (!split_path)
		return (false);
	while (*split_path)
	{
		exec_path = ft_strjoin(*split_path, "/");
		if (!exec_path)
			break ;
		exec_path = ft_strjoin(exec_path, str);
		if (!exec_path)
			break ;
		if (access(exec_path, X_OK) != -1)
			return (exec_path);
		free(exec_path);
		split_path++;
	}
}
