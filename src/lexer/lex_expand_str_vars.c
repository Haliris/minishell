/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_expand_str_vars.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:41:19 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/19 11:47:38 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char	*extract_key_from_str(char *str, size_t start)
{
	size_t	end;

	end = start + 1;
	while (str[end] && !is_delim(str[end]))
		end++;
	if (end == start + 1)
		return (NULL);
	return (ft_substr(str, start + 1, end - start - 1));
}

static char	*prepare_strings(char *str, char *key, size_t key_idx)
{
	char	*pre_str;
	char	*post_str;
	char	*result;

	pre_str = NULL;
	if (key_idx > 0)
		pre_str = ft_substr(str, 0, key_idx);
	else
		pre_str = ft_strdup("");
	if (!pre_str)
		return (NULL);
	post_str = ft_substr(str, key_idx + ft_strlen(key) + 1,
				ft_strlen(str) - (key_idx + ft_strlen(key) + 1));
	if (!post_str)
	{
		free(pre_str);
		return (NULL);
	}
	result = ft_strjoin(pre_str, post_str);
	free(pre_str);
	free(post_str);
	return (result);
}

static void	impute_var_val(char **str, char *val, char *key, size_t key_idx)
{
	char	*temp;
	char	*new_str;

	temp = prepare_strings(*str, key, key_idx);
	if (!temp)
		return ;
	new_str = ft_strjoin(temp, val);
	if (new_str)
		replace_str(str, new_str);
	free(temp);
}

static void	expand_single_var(t_data *data, char **str, size_t key_idx)
{
	char	*val;
	char	*key;

	key = extract_key_from_str(*str, key_idx);
	if (!key)
		return ;
	val = get_nestedval(data->env_vars, key);
	if (val)
	{
		impute_var_val(str, val, key, key_idx);
		free(val);
	}
	else
		impute_var_val(str, "", key, key_idx);
	free(key);
}

void	expand_string_var(t_data *data, char **str)
{
	size_t	i;
	char	expanded[4096];

	i = 0;
	ft_bzero(expanded, 4096);
	while ((*str) && (*str)[i] && i < 4096)
	{
		if ((*str)[i] == '$' && !is_delim((*str)[i + 1]) && expanded[i] == 0)
		{
			expand_single_var(data, str, i);
			expanded[i] = 1;
		}
		else
			i++;
	}
}
