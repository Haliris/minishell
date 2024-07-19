/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:29:12 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/19 18:17:15 by bthomas          ###   ########.fr       */
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

static int	update_old_pwd(t_data *data)
{
	char	*key;
	char	*val;

	key = "OLDPWD";
	val = get_cwd();
	if (!val)
		return (1);
	return (replace_var(&data->env_vars, key, val));
}

void	call_cd(t_data *data, char **cmd)
{
	char	*p;
	char	*cwd;

	if (!cmd[1] || ft_strcmp(cmd[1], "-") == 0)
		return ;
	p = cmd[1];
	if (var_in_str(cmd[1]))
		expand_string_var(data, &p);
	update_old_pwd(data);
	if (chdir(p) != 0)
	{
		ft_printf("Error: invalid path for cd '%s': %s\n", p, strerror(errno));
		return ;
	}
	cwd = get_cwd();
	if (!cwd)
		return ;
	add_var(&data->env_vars, "PWD", cwd);
}

#undef POSIX_MAX_PATH
