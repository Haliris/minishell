/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_expand_str_vars.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:41:19 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/26 14:18:31 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*extract_key_from_str(char *str, size_t start)
{
	size_t	end;

	if (ft_strncmp(str + start, "$$", 2) == 0)
		return (ft_strdup("$"));
	end = start + 1;
	while (str[end] && (!is_delim(str[end]) && !in(str[end], ";:/,.~^=")))
		end++;
	if (end == start + 1)
		return (NULL);
	return (ft_substr(str, start + 1, end - start - 1));
}

static char	*prepare_strings(char *str, char *key, char *val, size_t key_idx)
{
	char	*pre_str;
	char	*post_str;
	char	*result;

	pre_str = ft_substr(str, 0, key_idx);
	if (!pre_str)
		return (NULL);
	post_str = ft_substr(str, key_idx + ft_strlen(key) + 1
			- 1 * (ft_strcmp("$?", key) == 0),
			ft_strlen(str) - key_idx - ft_strlen(key) - 1
			+ 1 * (ft_strcmp("$?", key) == 0));
	if (!post_str)
	{
		free(pre_str);
		return (NULL);
	}
	result = ft_strjoin3(pre_str, val, post_str);
	(free(pre_str), free(post_str));
	return (result);
}

static void	impute_var_val(char **str, char *val, char *key, size_t key_idx)
{
	char	*new_str;

	if (!key)
		return ;
	new_str = prepare_strings(*str, key, val, key_idx);
	if (new_str)
		replace_str(str, new_str);
}

static void	expand_single_var(t_data *data, char **str, size_t key_idx)
{
	char	*val;
	char	*key;

	key = extract_key_from_str(*str, key_idx);
	if (!key)
		return ;
	if (in_vlist(data->env_vars, key))
		val = get_nestedval(data->env_vars, key);
	else
		val = ft_strdup("");
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
	size_t	len;
	size_t	i;
	char	*exit_code_str;

	i = 0;
	if (!str || !*str)
		return ;
	len = ft_strlen(*str);
	while (i < ft_strlen(*str))
	{
		if ((*str)[i] == '$' && (*str)[i + 1] && (*str)[i + 1] == '?')
		{
			exit_code_str = ft_itoa(data->errcode);
			if (!exit_code_str)
				continue ;
			impute_var_val(str, exit_code_str, "$?\0", i);
			free(exit_code_str);
		}
		else if ((*str)[i] == '$' && (!is_delim((*str)[i + 1])
			|| (*str)[i + 1] == '$'))
			expand_single_var(data, str, i);
		i++;
	}
}
