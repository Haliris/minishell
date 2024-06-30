/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bento <bento@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:48:06 by bento             #+#    #+#             */
/*   Updated: 2024/06/30 08:26:08 by bento            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	build_lex_tab2(t_token *token, char *input, size_t start_idx, size_t i)
{
	//
}

void	build_lex_tab1(t_token *token, char *input)
{
	size_t	i;
	size_t	start_idx;

	i = 0;
	start_idx = 0;
	while (input[start_idx])
	{
		if (is_space(input[start_idx]))
			start_idx++;
		else if (ft_isdigit(input[start_idx]))
			token[i] = get_num_tk(input, start_idx);
		else if (in(input[start_idx], "+-*/%%"))
			token[i] = get_op_tk(input, start_idx);
		else if (input[start_idx] == '"' || input[start_idx] == '\'')
			token[i] = get_string_tk(input, start_idx);
		if (token[i].type == TK_INVALID)
		{ // temporary, just while in development
			printf("Invalid token: %s\n", token[i].lexstr);
			exit(1);
		}
		if (token[i].lexstr == NULL)
			build_lex_tab2(token, input, start_idx, i);
		else
			i += ft_strlen(token[i].lexstr);
	}
}

t_token	*lexer(char *input)
{
	t_token	*token;

	token = malloc(sizeof(t_token) * ft_strlen(input));
	if (!token)
		return (NULL);
	build_lex_tab1(token, input);
}
