/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_bools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 12:36:56 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/23 07:04:41 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

bool	is_delim(char c)
{
	return (in(c, "$ \t\n\v\f\r=()<>|\"\'"));
}

bool	var_in_str(char *s)
{
	size_t	i;

	i = 0;
	if (ft_strcmp("$$", s) == 0 || ft_strcmp("$?", s) == 0)
		return (true);
	while (s[i] && s[i + 1])
	{
		if (s[i] == '$' && in(s[i + 1], "$?"))
			return (true);
		else if (s[i] == '$' && s[i + 1] && !is_delim(s[i + 1])
			&& !in(s[i + 1], ":/,.~^="))
			return (true);
		i++;
	}
	return (false);
}

static bool	space_before_last_equals(char *input, size_t idx)
{
	while (input[idx] != '=')
		idx--;
	idx--;
	if (is_space(input[idx - 1]))
		return (true);
	return (false);
}

bool	is_invalid_export(t_data *data, size_t curr_idx)
{
	t_token	*last_tk;

	last_tk = lex_get_last_token(data);
	if (last_tk && ft_strcmp("=", last_tk->lexstr) == 0)
	{
		if (last_tk->prev && last_tk->prev->prev
			&& ft_strcmp("export", last_tk->prev->prev->lexstr) == 0)
		{
			if (is_space(data->input[curr_idx]))
				return (true);
			else if (space_before_last_equals(data->input, curr_idx))
				return (true);
		}
	}
	return (false);
}

bool	invalid_path_char(char c)
{
	if (!ft_isalnum(c))
		if (c != '_')
			return (true);
	return (false);
}
