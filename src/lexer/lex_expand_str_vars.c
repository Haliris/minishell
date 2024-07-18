/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_expand_str_vars.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:15:20 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/18 11:52:01 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char	*extract_key_from_str(char *str, size_t *start)
{
	size_t	end;

	end = *start + 1;
	while (str[end] && !in(str[end], "$\"\' \t\r\v\n\f"))
		end++;
	if (end == *start + 1)
		return (NULL);
	return (ft_substr(str, *start + 1, end - *start - 1));
}

void	replace_str(char **old, char *new)
{
	if (!old || !*old)
		return ;
	free(*old);
	*old = new;
	return ;
}

static void	impute_var_val(char **str, char *val, char *key, size_t key_idx)
{
	char	*pre_str;
	char	*post_str;
	char	*temp;
	char	*new_str;

	pre_str = NULL;
	if (key_idx != 0)
	{
		pre_str = ft_substr(*str, 0, key_idx - 1);
		if (!pre_str)
			return ;
	}
	temp = ft_strjoin(pre_str, val);
	if (!temp)
		return ;
	if (ft_strlen(*str) == key_idx + ft_strlen(key))
		return (replace_str(str, temp), free(pre_str));
	post_str = ft_substr(*str, key_idx + ft_strlen(key),
			ft_strlen(*str) - key_idx + ft_strlen(key));
	if (!post_str)
		return (free(temp), free(pre_str));
	new_str = ft_strjoin(temp, post_str);
	if (new_str)
		replace_str(str, new_str);
	return (free(temp), free(post_str), free(pre_str));
}

/* e.g., "hello $world" world=mark, "hello mark"*/
void	expand_string_var(t_data *data, char **str)
{
	char	*val;
	char	*key;
	size_t	i;
	size_t	key_start;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] && (*str)[i] == '$' &&
			!in((*str)[i + 1], "$ \t\n\v\f\r=()<>|"))
		{
			key_start = i;
			key = extract_key_from_str(*str, &i);
			if (!key)
				continue ;
			val = get_varval(data->env_vars, key);
			impute_var_val(str, val, key, key_start);
			free(key);
			i = key_start;
		}
		else
			i++;
	}
	free(val);
	free(key);
}
