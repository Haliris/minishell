/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:32:33 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/16 10:33:55 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	extract_key_val(t_data *data, t_token *token)
{
	char	*key;
	char	*val;

	key = ft_strdup(token->lexstr);
	if (!key)
		return ;
	token = token->next->next;
	val = ft_strdup(token->lexstr);
	if (!val)
	{
		free(key);
		return ;
	}
	if (add_var(&data->env_vars, key, val))
	{
		ft_printf("Error: could not export variable\n.");
		free(key);
		free(val);
	}
	return ;
}

void	export(t_data *data, t_token *token)
{
	token = token->next;
	if (!token || token->type == TK_PIPE)
		return (print_env(data));
	if (token->lexstr[0] == '=')
	{
		ft_printf("minishell: export: '%s': not a valid identifier\n",
			token->lexstr);
		return ;
	}
	if (!token || token->next->type != TK_OPERATOR || !token->next->next)
		return ;
	extract_key_val(data, token);
}
