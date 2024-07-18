/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_expand_str_vars.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:15:20 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/18 16:54:16 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char	*extract_key_from_str(char *str, size_t start)
{
	size_t	end;

	end = start + 1;
	while (str[end] && !in(str[end], "$\"\' \t\r\v\n\f"))
		end++;
	if (end == start + 1)
		return (NULL);
	return (ft_substr(str, start + 1, end - start - 1));
}

void	replace_str(char **old, char *new)
{
	if (!old || !*old)
		return ;
	free(*old);
	*old = new;
	return ;
}

static void	null_val_replace(char **str, char *val, char *key)
{
	if (!val && ft_strlen(*str) == (ft_strlen(key) + 1))
	{
		*str = NULL;
	}
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
		pre_str = ft_substr(*str, 0, key_idx);
		if (!pre_str)
			return ;
	}
	temp = ft_strjoin(pre_str, val);
	if (!temp)
		return ;
	if (ft_strlen(*str) == key_idx + ft_strlen(key) + 1)
		return (replace_str(str, temp), free(pre_str));
	post_str = ft_substr(*str, key_idx + ft_strlen(key) + 1,
			ft_strlen(*str) - key_idx + ft_strlen(key) + 1);
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
	int		var_count;

	i = 0;
	var_count = count_str_vars(*str);
	while ((*str) && (*str)[i] && var_count)
	{
		if ((*str)[i] && (*str)[i] == '$' && is_delim((*str)[i]) && var_count--)
		{
			key = extract_key_from_str(*str, i);
			if (!key)
				continue ;
			val = get_varval(data->env_vars, key);
			null_val_replace(str, val, key);
			impute_var_val(str, val, key, i);
			free(key);
			i += ft_strlen(val);
			if (val)
				free(val);
		}
		else
			i++;
	}
}
