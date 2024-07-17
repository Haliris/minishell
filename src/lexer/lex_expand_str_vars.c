/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_expand_str_vars.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:15:20 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/17 16:27:39 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char	*extract_key_from_str(char *str, size_t *start)
{
	size_t	end;

	end = *start + 1;
	while (str[end] && !is_space(str[end]) && str[end] != '$')
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
	size_t	i;
	char	*pre_str;
	char	*post_str;
	char	*temp;
	char	*new_str;

	pre_str = ft_substr(*str, 0, key_idx);
	if (!pre_str)
		return ;
	if (!val)
		val = "";
	temp = ft_strjoin(pre_str, val);
	free(pre_str);
	if (!temp)
		return ;
	i = key_idx + ft_strlen(key) + 1;
	post_str = ft_substr(*str, i, ft_strlen(*str) - i);
	if (!post_str)
		return (free(temp));
	new_str = ft_strjoin(temp, post_str);
	free(temp);
	free(post_str);
	if (new_str)
		replace_str(str, new_str);
}

/* e.g., "hello $world" world=mark, "hello mark"*/
void	expand_string_var(t_data *data, char **str)
{
	char	*val;
	char	*key;
	size_t	i;
	size_t	key_start;

	if (!str || !*str || !data)
		return ;
	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$' && (*str)[i + 1] &&
			(!in((*str)[i + 1], "$() \n\t\v\f\r")))
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
}
