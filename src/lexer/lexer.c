/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:48:06 by bento             #+#    #+#             */
/*   Updated: 2024/07/10 18:47:48 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	build_tokenlist2(t_data *data, size_t input_len, size_t *i)
{
	while (*i < input_len)
	{
		while (is_space(data->input[*i]))
			*i ++;
		if (empty_quote(data->input, *i))
			*i += 2;
	}
}

/* Need to split this in 2 or 3 functions */
static void	build_tokenlist1(t_data *data, size_t input_len)
{
	size_t	i;
	t_token	*curr_tk;

	curr_tk = NULL;
	i = 0;
	while (i < input_len)
	{
		while (is_space(data->input[i]))
			i++;
		while (empty_quote(data->input, i))
			i += 2;
		if (data->input[i] == '\"' || data->input[i] == '\'')
			curr_tk = get_string_tk(data, data->input, i);
		else if
			curr_tk = 
		i += ft_strlen(curr_tk->lexstr);
		lex_add_token(data, curr_tk);
	}
	return (0);
}

/* Unfortunately we're not allowed to use case statmements :( */
int	lexer(t_data *data)
{
	size_t	input_len;

	input_len = ft_strlen(data->input);
	if (build_tokenlist(data, input_len))
		return (1);
	return (0);
}
