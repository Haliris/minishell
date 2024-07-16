/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 16:48:40 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/16 10:01:07 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_env(t_data *data, char **env)
{
	char	*key;
	char	*val;

	while (*env)
	{
		key = get_substr(*env, 0);
		if (!key)
			return (1);
		while (**env != '=')
			(*env)++;
		(*env)++;
		val = ft_strdup(*env);
		if (!val)
		{
			free(key);
			return (1);
		}
		if (add_var(&data->env_vars, key, val))
			return (1);
		(env)++;
	}
	return (0);
}

int	init(t_data *data, char **env)
{
	handle_signals();
	data->token = NULL;
	return (init_env(data, env));
}
