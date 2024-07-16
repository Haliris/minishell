/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:29:12 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/16 15:01:44 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sh_cd(t_data *data, char *cmd)
{
	cmd += 2;
	while (*cmd && is_space(*cmd))
		cmd++;
	if (!*cmd)
		return ;
	expand_string_var(data, &cmd);
	if (chdir(cmd) != 0)
		ft_printf("minishell: cd: '%s': %s\n", cmd,
			strerror(errno));
}
