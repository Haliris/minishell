/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_env_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 11:58:51 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/14 17:29:04 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/* add function to expand out $env vars when within double quotes. */
char	*get_var(t_data *data, char *key)
{
	char	*val;

	val = ht_getval(data->env_vars, key);
	if (!val)
		val = ht_getval(data->local_vars, key);
	return (val);
}
