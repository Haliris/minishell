/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:32:33 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/15 17:13:34 by bthomas          ###   ########.fr       */
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

/* if in local, move to env, if not in either, create in env  */

/*
export var1=wow

or
$var1=wow
export $var1
*/
void	export(t_data *data, t_token *token)
{
	char	*key;
	char	*val;

	token = token->next;
	if (token->lexstr[0] == '=')
	{
		ft_printf("minishell: export: '%s': not a valid identifier\n");
		return ;
	}
	if (token->lexstr[0] == '$')
	{

	}
}
