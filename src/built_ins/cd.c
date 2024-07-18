/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:29:12 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/18 17:06:08 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	call_cd(t_data *data, char **cmd)
{
	char	*p;

	if (!cmd[1] || cmd[1][0] == '-')
		return ;
	p = cmd[1];
	if (var_in_str(cmd[1]))
		expand_string_var(data, &p);
	if (chdir(p) != 0)
		ft_printf("Error: invalid path for cd '%s': %s\n", p, strerror(errno));
}
