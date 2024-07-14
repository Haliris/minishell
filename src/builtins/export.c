/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:32:33 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/14 17:35:31 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ht_delete_key(t_hash_table *table, char *key)
{
	
}

/* I remember there was something to do with using env, will need to discuss */
static void	print_env(t_data *data)
{
	size_t	i;

	i = 0;
	while (data->env && data->env[i])
	{
		ft_printf("declare -x %s\n", data->env[i]);
		i++;
	}
}

/* if in local, move to env, if not in either, create in env  */
void	export(t_data *data, t_token *token)
{
	char	*val;

	if (token->type == TK_BUILTIN)
		token = token->next;
	if (!token)
		return (print_env(data));
	if (token == TK_OPERATOR && token->lexstr[0] == '=')
		token = token->next;
	if (!token)
	{
		printf("export: '=': not a valid identifier\n");
		return ;
	}
}
