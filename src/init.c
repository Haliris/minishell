/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 16:48:40 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/15 12:16:30 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	build_env(t_hash_table *table, char **env)
{
	size_t		i;
	t_ht_entry	*entry;

	if (!env)
		return (1);
	i = 0;
	while (env[i])
	{
		entry = malloc(sizeof(entry));
		if (!entry)
			return (1);
		entry->key = get_substr(env[i], 0);
		while (*env[i] != '=')
			env[i]++;
		env[i]++;
		entry->value = ft_strdup(env[i]);
		if (!entry->key || !entry->value)
			return (1);
		if (ht_set_entry(table, entry))
			return (1);
		i++;
	}
	return (0);
}

int	init(t_data *data, char **env)
{
	handle_signals();
	data->token = NULL;
	data->local_vars = ht_create();
	data->env_vars = ht_create();
	if (!data->env_vars || !data->local_vars)
	{
		ft_printf("Err: failed to create hash tables.\n");
		exit(lex_clean_exit(data, 1));
	}
	if (build_env(data->env_vars, env))
	{
		ft_printf("Err: failed to build env table.\n");
		exit(lex_clean_exit(data, 1));
	}
	return (0);
}
