/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:29:12 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/19 12:18:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define POSIX_MAX_PATH 4096

static char	*get_cwd(void)
{
	char	*status;
	char	*cwd;

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
	else
		return (cwd);
}

static void	update_env(char *cwd, t_varlist *env, char *var)
{
	t_varlist	*roaming;

	roaming = env;
	while (roaming)
	{
		if (ft_strcmp(roaming->key, var) == 0)
		{
			free(roaming->val);
			roaming->val = ft_strdup(cwd);
			if (!roaming->val)
				ft_putstr_fd("minishell: error updating env\n", STDERR_FILENO);
			break ;
		}
		roaming = roaming->next;
	}
}

void	call_cd(t_data *data, char **cmd)
{
	char	*p;
	char	*cwd;

	cwd = NULL;
	if (cmd[1] == NULL)
		return ;
	p = cmd[1];
	if (var_in_str(cmd[1]))
		expand_string_var(data, &p);
	cwd = get_cwd();
	update_env(cwd, data->env_vars, "OLDPWD");
	free(cwd);
	if (chdir(p) != 0)
		ft_printf("Error: invalid path for cd '%s': %s\n", p, strerror(errno));
	cwd = get_cwd();
	update_env(cwd, data->env_vars, "PWD");
	free(cwd);
}

#undef POSIX_MAX_PATH