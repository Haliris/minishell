/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bento <bento@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:48:06 by bento             #+#    #+#             */
/*   Updated: 2024/06/29 20:10:39 by bento            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	get_num_tk(char *input, size_t start_idx)
{
	size_t	i;

	i = start_idx;
	while (ft_isdigit(input[i]))
		i++;
	return (get_token(ft_substr(input, start_idx, i - start_idx), TK_NUMBER));
}

t_token	get_op_tk(char *input, size_t start_idx)
{
	if (!in(input[start_idx], "+-*/%%"))
		return (get_token("", TK_INVALID));
	return (get_token(ft_substr(input, start_idx, 1), TK_OPERATOR));
}

t_token	get_executable(char *input, size_t start_idx)
{
	size_t	i;
	char	*lexstr;

	i = start_idx;
	while (input[i] && !is_space(input[i]) && !in(input[i], "|<>"))
		i++;
	lexstr = ft_substr(input, start_idx, i - start_idx);
	if (!lexstr)
		return (get_token("", TK_INVALID));
	return (get_token(lexstr, TK_EXECUTABLE));
}

t_token *lexer(char *input)
{
	t_token	*token;

	token = NULL;
	return (token);
}