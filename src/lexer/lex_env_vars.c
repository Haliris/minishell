/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_env_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 11:58:51 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/08 14:27:26 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// Replace this with getenv function

//add function to expand out $env vars only when within double quotes. replace lexstr

char	*get_env_var(char *var_str, t_data *data)
{
	char	*search_str;
	size_t	search_str_len;
	size_t	i;
	size_t	len;

	search_str = ft_strjoin(var_str, "=");
	if (!search_str)
		return (NULL);
	search_str++;
	search_str_len = ft_strlen(search_str);
	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], search_str, search_str_len) == 0)
		{
			len = ft_strlen(data->env[i]);
			free(search_str);
			return (ft_substr(data->env[i], search_str_len,
					len - search_str_len));
		}
		i++;
	}
	return (NULL);
}
