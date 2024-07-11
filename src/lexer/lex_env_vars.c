/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_env_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 11:58:51 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/11 08:15:52 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/* Replace this with getenv function */

/* add function to expand out $env vars only when within double quotes. 
replace lexstr */

char	*get_env_var(char *var_str)
{
	char	*path;

	path = getenv(var_str);
	if (!path)
		return (NULL);
	else
		return (ft_strdup(path));
}
