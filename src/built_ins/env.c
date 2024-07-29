/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 10:00:44 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/29 14:16:22 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

void	call_env(t_data *data, char **command)
{
	t_varlist	*curr;

	if (command[1])
	{
		ft_putstr_fd("env: \'", 2);
		ft_putstr_fd(command[1], 2);
		ft_putstr_fd("\': Permission denied.\n", 2);
		return ;
	}
	curr = data->env_vars;
	while (curr)
	{
		if (curr->key)
			ft_printf("%s=\"%s\"\n", curr->key, curr->val);
		curr = curr->next;
	}
}
