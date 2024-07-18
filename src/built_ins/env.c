/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 10:00:44 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/18 10:05:20 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

void	call_env(t_data *data)
{
	t_varlist	*curr;

	curr = data->env_vars;
	while (curr)
	{
		if (curr->key)
			ft_printf("%s=\"%s\"\n", curr->key, curr->val);
		curr = curr->next;
	}
}
