/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_retrieve_tk1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 08:04:48 by bento             #+#    #+#             */
/*   Updated: 2024/07/08 13:45:17 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	get_num_tk(char *input, size_t *start_idx)
{
	size_t	i;
	t_token	num_tk;

	i = *start_idx;
	while (ft_isdigit(input[i]))
		i++;
	num_tk = get_token(ft_substr(input, *start_idx, i - *start_idx), TK_NUMBER);
	*start_idx += ft_strlen(num_tk.lexstr);
	return (num_tk);
}

t_token	get_string_tk(char *input, size_t *start_idx)
{
	size_t			i;
	t_token			str_tk;
	char			*lexstr;
	unsigned char	quote;

	i = *start_idx + 1;
	quote = input[*start_idx];
	while (input[i] && input[i] != quote)
		i++;
	lexstr = ft_substr(input, *start_idx, i - *start_idx + 1);
	if (!lexstr)
		return (get_token(NULL, TK_INVALID));
	str_tk = get_token(lexstr, TK_STRING);
	*start_idx += ft_strlen(str_tk.lexstr);
	return (str_tk);
}

t_token	get_word_tk(char *input, size_t *start_idx)
{
	char	*lexstr;
	t_token	word_tk;

	lexstr = get_substr(input, *start_idx);
	if (!lexstr)
		return (get_token(NULL, TK_INVALID));
	word_tk = get_token(lexstr, TK_WORD);
	*start_idx += ft_strlen(word_tk.lexstr);
	return (word_tk);
}

t_token	get_flag_tk(char *input, size_t *start_idx)
{
	char	*lexstr;
	t_token	flag_tk;

	lexstr = get_substr(input, *start_idx);
	if (!lexstr)
		return (get_token(NULL, TK_INVALID));
	flag_tk = get_token(lexstr, TK_FLAG);
	*start_idx += ft_strlen(flag_tk.lexstr);
	return (flag_tk);
}
