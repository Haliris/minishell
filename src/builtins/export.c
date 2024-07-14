/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:32:33 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/13 13:47:05 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	valid uses:
		export VAR1="value"

		VAR1="value"
		export VAR1
*/


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

/* need to create hashmap before continuing */
void	export(t_data *data, t_token *token)
{
	t_envvar	var;

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
