/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 16:48:40 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/28 17:11:22 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_val(char *s)
{
	size_t	i;

	i = 0;
	while (s[i - 1] != '=')
		i++;
	if (i == 0)
		return (NULL);
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
		{
			free(key);
			return (1);
		}
		if (add_var(&data->env_vars, key, val))
		{
			free(key);
			free(val);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	add_dummies(t_data *data)
{
	char	*ppid;
	char	*val_ppid;
	char	*uid;
	char	*val_uid;

	ppid = ft_strdup("$");
	if (!ppid)
		return ;
	val_ppid = ft_strdup("[1]....883183.segmentation.fault.(core.dumped).SIKE");
	if (!val_ppid)
		return (free(ppid));
	if (add_var(&data->env_vars, ppid, val_ppid))
		return (free(ppid), free(val_ppid));
	uid = ft_strdup("UID");
	if (!uid)
		return ;
	val_uid = ft_strdup("UID_PLACEHOLDER");
	if (!val_uid)
		return (free(uid));
	if (add_var(&data->env_vars, uid, val_uid))
		return (free(uid), free(val_uid));
}

int	init(t_data *data, char **env)
{
	init_signals();
	data->token = NULL;
	data->prompt = NULL;
	data->env_vars = NULL;
	data->errcode = EXIT_SUCCESS;
	data->parsedata = ft_calloc(1, sizeof(t_parser));
	if (!data->parsedata)
		return (PANIC);
	data->parsedata->table = NULL;
	data->parsedata->next = NULL;
	data->heredata = NULL;
	data->piddata = NULL;
	data->prev_fd = STDIN_FILENO;
	g_sig_offset = 0;
	if (init_env(data, env))
		return (PANIC);
	add_dummies(data);
	return (0);
}
