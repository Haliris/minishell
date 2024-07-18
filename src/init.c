/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 16:48:40 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/18 12:57:05 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_val(char *s)
{
	size_t	i;

	i = 0;
	while (s[i - 1] != '=')
		i++;
	return (ft_substr(s, i, ft_strlen(s) - i));
}

static int	init_env(t_data *data, char **env)
{
	char	*key;
	char	*val;
	size_t	i;

	i = 0;
	while (env[i])
	{
		key = get_substr(env[i], 0);
		if (!key)
			return (1);
		val = extract_val(env[i]);
		if (!val)
			return (1);
		if (add_var(&data->env_vars, key, val))
			return (1);
		i++;
	}
	return (0);
}

int	init(t_data *data, char **env)
{
	handle_signals();
	data->token = NULL;
	data->env_vars = NULL;
	data->parsedata = malloc(sizeof(t_parser));
	if (!data->parsedata)
		return (PANIC);
	data->parsedata->table = NULL;
	data->parsedata->next = NULL;
	data->heredata = malloc(sizeof(t_heredoc_data));
	if (!data->heredata)
		return (PANIC);
	data->heredata->heredoc = NULL;
	data->heredata->next = NULL;
	return (init_env(data, env));
}
