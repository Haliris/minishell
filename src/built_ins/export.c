/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:32:33 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/20 12:34:21 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

int	get_cmd_len(char **cmd)
{
	int	len;

	if (!cmd || !*cmd)
		return (0);
	len = 0;
	while (cmd[len])
		len++;
	return (len);
}

static void	print_env(t_data *data)
{
	t_varlist	*curr;

	curr = data->env_vars;
	while (curr)
	{
		if (curr->key)
			ft_printf("export %s=\"%s\"\n", curr->key, curr->val);
		curr = curr->next;
	}
}

/* unfinished, need to add in / replace var */
void	call_export(t_data *data, char **cmd)
{
	char	*key;
	char	*val;
	int		cmd_len;

	cmd_len = get_cmd_len(cmd);
	if (cmd_len == 1)
		return (print_env(data));
	if (cmd[1][0] == '=')
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return ;
	}
	if (cmd_len < 4 || ft_strcmp(cmd[2], "="))
		return ;
	key = ft_strdup(cmd[1]);
	if (!key)
		return ;
	val = ft_strdup(cmd[3]);
	if (!val)
		return (free(key));
	if (add_var(&data->env_vars, key, val))
		return (ft_putendl_fd("Error: export allocation failed.", 2),
			free(key), free(val));
}
