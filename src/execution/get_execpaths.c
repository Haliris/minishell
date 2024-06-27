/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_execpaths_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:44:37 by jteissie          #+#    #+#             */
/*   Updated: 2024/06/15 17:16:48 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "execution.h"

void	cat_slash(char **exec_paths)
{
	int		i;
	char	*safety_p;

	i = 0;
	if (!exec_paths)
		return ;
	while (exec_paths[i])
	{
		safety_p = ft_str_realloc_join(exec_paths[i], "/");
		if (!safety_p)
		{
			trash(exec_paths);
			return ;
		}
		exec_paths[i] = safety_p;
		i++;
	}
}

char	*get_path(char *av, char **env)
{
	char	*control;
	int		i;

	i = 0;
	while (env[i])
	{
		control = ft_strjoin(env[i], av);
		if (access(control, F_OK | X_OK) == 0)
		{
			trash(env);
			return (control);
		}
		i++;
		free(control);
	}
	trash(env);
	return (NULL);
}

char	*get_execpath(char **envp, char *av)
{
	int		i;
	char	*check_p;
	char	**env_paths;
	char	*exec_path;

	i = 0;
	check_p = NULL;
	while (envp[i])
	{
		check_p = ft_strnstr(envp[i], "PATH=", 5);
		if (check_p)
		{
			check_p = ft_substr(envp[i], 5, ft_strlen(envp[i]));
			break ;
		}
		i++;
	}
	if (!check_p)
		return (NULL);
	env_paths = ft_split(check_p, ':');
	free(check_p);
	cat_slash(env_paths);
	exec_path = get_path(av, env_paths);
	return (exec_path);
}
