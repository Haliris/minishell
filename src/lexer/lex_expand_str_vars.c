/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_expand_str_vars.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:15:20 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/16 12:03:40 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char	*extract_key_from_str(char *str, size_t start)
{
	size_t	end;

	end = start;
	while (str[end] && !is_space(str[end]) && str[end] != '$')
		end++;
	if (end == start)
		return (NULL);
	return (ft_substr(str, start, end - start));
}

void	replace_str(char **old, char *new)
{
	char	*temp;

	if (!old || !*old)
		return ;
	temp = *old;
	*old = new;
	free(temp);
	return ;
}

static void	impute_var_val(char **str, char *val, char *key, size_t key_idx)
{
	size_t	i;
	char	*pre_str;
	char	*post_str;
	char	*temp;

	pre_str = ft_substr(*str, 0, key_idx - 1);
	if (!pre_str)
		return ;
	temp = ft_strjoin(pre_str, val);
	if (!temp)
		return ;
	i = key_idx + ft_strlen(key);
	while (*str[i])
		i++;
	if (i == key_idx + ft_strlen(key))
		return (free(pre_str), replace_str(str, temp));
	post_str = ft_substr(*str, i, ft_strlen(*str) - i);
	if (!post_str)
		return (free(pre_str), free(temp));
	return (replace_str(str, ft_strjoin(temp, post_str)),
		free(pre_str), free(temp), free(post_str));
}

/* e.g., "hello $world" world=mark, "hello mark"*/
void	expand_string_var(t_data *data, char **str)
{
	char	*val;
	char	*key;
	size_t	i;

	if (!*str || !data)
		return ;
	i = 0;
	while (*str[i])
	{
		if (*str[i] == '$' && !is_space(*str[i + 1]) && *str[i + 1] != '$')
		{
			key = extract_key_from_str(*str, i);
			if (!key)
				continue ;
			val = get_varval(data->env_vars, key);
			impute_var_val(str, val, key, i);
		}
		i++;
	}
}
