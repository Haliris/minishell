/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:29:12 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/29 16:26:31 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define POSIX_MAX_PATH 4096

char	*get_cwd(void)
{
	char	*status;
	char	*cwd;
	char	*ret;

	cwd = ft_calloc(POSIX_MAX_PATH, sizeof(char *));
	if (!cwd)
	{
		ft_putstr_fd("minishell: malloc error\n", STDERR_FILENO);
		return (NULL);
	}
	status = getcwd(cwd, POSIX_MAX_PATH);
	if (!status)
	{
		ft_putstr_fd("minishell: getcwd error\n", STDERR_FILENO);
		free(cwd);
		return (NULL);
	}
	ret = ft_strdup(cwd);
	free(cwd);
	if (!ret)
		return (NULL);
	return (ret);
}

static int	update_pwd(t_data *data, bool is_old)
{
	char	*val;
	char	*key;

	if (!is_old)
		key = ft_strdup("PWD");
	else
		key = ft_strdup("OLDPWD");
	if (!key)
		return (1);
	val = get_cwd();
	if (!val)
		return (free(key), 1);
	return (add_var(&data->env_vars, key, val));
}

void	call_cd(t_data *data, char **cmd)
{
	char	*p;

	if (!cmd[1] || ft_strcmp(cmd[1], "-") == 0)
		return ;
	if (cmd[2])
		return (ft_putendl_fd("minishell: cd: too many arguments", 2));
	p = cmd[1];
	update_pwd(data, true);
	if (chdir(p) != 0)
	{
		ft_putstr_fd("Error: invalid path for cd '", 2);
		ft_putstr_fd(p, 2);
		ft_putstr_fd("': ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return ;
	}
	update_pwd(data, false);
}

#undef POSIX_MAX_PATH
