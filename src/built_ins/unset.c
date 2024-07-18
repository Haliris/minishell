/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 10:23:03 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/18 10:26:00 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

void	call_unset(t_data *data, char **cmd)
{
	char	*key;

	if (!cmd[1])
		return ;
	key = cmd[1];
	del_varlist_key(data->env_vars, key);
}
