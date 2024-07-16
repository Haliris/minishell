/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 16:48:40 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/16 14:56:06 by bthomas          ###   ########.fr       */
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

int	init(t_data *data, char **env, t_parser *parser, t_heredoc_data *heredata)
{
	handle_signals();
	data->token = NULL;
	data->env_vars = NULL;
	parser->node = NULL;
	heredata->heredoc = NULL;
	heredata->next = NULL;
	return (init_env(data, env));
}