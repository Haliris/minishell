/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:48:06 by bento             #+#    #+#             */
/*   Updated: 2024/07/08 13:49:39 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	build_tokenlist(t_data *data, size_t input_len)
{
	size_t	i;
	t_token	last_tk;

	i = 0;
	while (i < input_len)
	{
		if (is_space(data->input[i]))
			i++;
		else if (data->input[i] == '-')
			lex_add_token(data, get_flag_tk(data->input, &i));
		else if (data->input[i] == '\"' || data->input[i] == '\'')
			lex_add_token(data, get_string_tk(data->input, &i));
		else if (ft_isdigit(data->input[i]))
			lex_add_token(data, get_num_tk(data->input, &i));
		else
			lex_add_token(data, get_word_tk(data->input, &i));
		last_tk = *lex_get_last_token(data);
		if (last_tk.type == TK_INVALID || last_tk.lexstr == NULL)
		{
			printf("Error, invalid token\n");
			return (1);
		}
		print_token(&last_tk);
	}
	return (0);
}

/* Unfortunately we're not allowed to use case statmements :( */
int	lexer(t_data *data)
{
	t_token	*token;
	size_t	input_len;

	input_len = ft_strlen(data->input);
	token = malloc(sizeof(t_token) * input_len);
	if (!token)
		return (1);
	if (build_tokenlist(data, input_len))
		return (1);
	return (0);
}
