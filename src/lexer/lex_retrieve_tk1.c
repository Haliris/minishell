/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_retrieve_tk1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 08:04:48 by bento             #+#    #+#             */
/*   Updated: 2024/07/07 17:27:32 by bthomas          ###   ########.fr       */
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

t_token	get_string_tk(char *input, size_t start_idx)
{
	size_t			i;
	char			*lexstr;
	unsigned char	quote;

	i = start_idx + 1;
	quote = input[start_idx];
	while (input[i] && input[i] != quote)
		i++;
	lexstr = ft_substr(input, start_idx, i - start_idx + 1);
	if (!lexstr)
		return (get_token(NULL, TK_INVALID));
	return (get_token(lexstr, TK_STRING));
}

t_token	get_word_tk(char *input, size_t start_idx)
{
	char	*lexstr;

	lexstr = get_substr(input, start_idx);
	if (!lexstr)
		return (get_token(NULL, TK_INVALID));
	return (get_token(lexstr, TK_WORD));
}

t_token	get_flag_tk(char *input, size_t start_idx)
{
	char	*lexstr;

	lexstr = get_substr(input, start_idx);
	if (!lexstr)
		return (get_token(NULL, TK_INVALID));
	return (get_token(lexstr, TK_FLAG));
}
