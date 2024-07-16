/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:32:33 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/16 15:08:33 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_empty_str(char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
	{
		if (!is_space(s[i]))
			return (false);
		i++;
	}
	return (true);
}

static void	print_env(t_data *data)
{
	t_varlist	*curr;

	curr = data->env_vars;
	while (curr)
	{
		if (curr->key)
			ft_printf("declare -x %s=\"%s\"\n", curr->key, curr->val);
		curr = curr->next;
	}
}

static char	*extract_key_val(char **split_cmd)
{
	size_t	i;

	i = 0;
	while (split_cmd[0][i] && i > 0 && split_cmd[0][i - 1] != '=')
		i++;
	return (ft_substr(split_cmd[0], i, ft_strlen(split_cmd[0]) - i));
}

static bool	export_err(char **split_cmd)
{
	size_t	i;

	if (split_cmd[0] && split_cmd[0][0] == '=')
	{
		ft_printf("minishell: export: '%s': not a valid identifier\n",
			split_cmd[0]);
		return (true);
	}
	if (split_cmd[1])
	{
		free_strarray(split_cmd);
		ft_printf("bad assignment\n");
		return (true);
	}
	i = 0;
	while (split_cmd[0][i] && split_cmd[0][i] != '-')
		i++;
	return (split_cmd[0][i] != '=');
}

/* unfinished, need to add in / replace var */
void	export(t_data *data, char *cmd)
{
	char	**split_cmd;
	char	*key;
	char	*val;

	cmd += 6;
	if (is_empty_str(cmd))
		return (print_env(data));
	split_cmd = ft_split(cmd, ' ');
	if (!split_cmd)
		return (ft_putendl_fd("Error: malloc failure.\n", 2));
	if (export_err(split_cmd))
		return (free_strarray(split_cmd));
	key = get_substr(split_cmd[0], 0);
	if (!key)
		return (free_strarray(split_cmd));
	val = extract_key_val(split_cmd);
	if (!val)
		return (free(key), free_strarray(split_cmd));
}
