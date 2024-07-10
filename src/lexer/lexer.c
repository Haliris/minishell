/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:48:06 by bento             #+#    #+#             */
/*   Updated: 2024/07/10 18:07:53 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	build_tokenlist2(t_data *data, size_t input_len, size_t i)
{
	t_token	*curr_tk;

	while (i < input_len)

}

/* Need to split this in 2 or 3 functions */
static int	build_tokenlist1(t_data *data, size_t input_len)
{
	size_t	i;
	t_token	*curr_tk;

	i = 0;
	while (i < input_len)
	{
		while (is_space(data->input[i]))
			i++;
		while (empty_quote(data->input, i))
			i += 2;
		if (data->input[i] == '-')
			curr_tk = get_flag_tk(data, data->input, i);
		else if (data->input[i] == '\"' || data->input[i] == '\'')
			curr_tk = get_string_tk(data, data->input, i);
		else if (ft_isdigit(data->input[i]))
			curr_tk = get_num_tk(data, data->input, i);
		else if (is_builtin(data->input, i))
			curr_tk = get_builtin_tk(data, data->input, i);
		else if (!is_space(data->input[i]))
			curr_tk = get_word_tk(data, data->input, i);
		else
			continue ;
		if (curr_tk->lexstr == NULL)
			return (1);
		i += ft_strlen(curr_tk->lexstr);
		print_token(curr_tk);
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
