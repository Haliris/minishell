/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:42:40 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/19 17:45:22 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define POSIX_MAX_PATH 4096

void	call_pwd(void)
{
	char	*cwd;
	char	*status;

	cwd = NULL;
	cwd = ft_calloc(POSIX_MAX_PATH, sizeof(char));
	if (!cwd)
	{
		ft_putstr_fd("minishell: pwd calloc error\n", STDERR_FILENO);
		return ;
	}
	status = getcwd(cwd, POSIX_MAX_PATH);
	if (!status)
		ft_putstr_fd("minishell: pwd error\n", STDERR_FILENO);
	else
	{
		ft_putstr_fd(cwd, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	free(cwd);
}

#undef POSIX_MAX_PATH
