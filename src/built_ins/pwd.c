/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:42:40 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/19 10:51:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fetch_pwd_var(t_data *data)
{
	t_varlist	*roaming;
	char		*path;

	roaming = data->env_vars;
	path = NULL;
	while (roaming)
	{
		if (ft_strcmp(roaming->key, "PWD") == 0)
		{
			path = roaming->val;
			break ;
		}
		roaming = roaming->next;
	}
	return (path);
}

void	call_pwd(t_data *data)
{
	char	*cwd;

	cwd = fetch_pwd_var(data);
	if (!cwd)
		ft_putstr_fd("minishell: pwd error\n", STDERR_FILENO);
	else
	{
		ft_putstr_fd(cwd, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
}
