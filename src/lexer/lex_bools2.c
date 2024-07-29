/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_bools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 12:36:56 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/29 14:12:46 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

bool	is_delim(char c, bool echo_str)
{
	if (!echo_str)
		return (in(c, "$ \t\n\v\f\r=<>|\"\'"));
	else
		return (in(c, "$ \t\n\v\f\r<>|\"\'"));
}

bool	var_in_str(char *s, char quote)
{
	size_t	i;

	if (quote && quote == '\'')
		return (false);
	i = 0;
	while (s[i] && s[i + 1])
	{
		if (s[i] == '$' && in(s[i + 1], "$?"))
			return (true);
		else if (s[i] == '$' && s[i + 1] && !is_delim(s[i + 1], false)
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
		if (in_builtin(last_tk, "export"))
		{
			if (space_before_last_equals(data->input, curr_idx))
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
