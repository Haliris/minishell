/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 10:23:03 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/22 13:28:03 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

void	call_unset(t_data *data, char **cmd)
{
	char	*key;

	if (!cmd[1])
		return ;
	key = cmd[1];
	if (cmd[2] && ft_strcmp(cmd[2], "=") == 0)
		return ;
	del_varlist_key(data->env_vars, key);
}
