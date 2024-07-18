/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_retrieve_tk1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 08:04:48 by bento             #+#    #+#             */
/*   Updated: 2024/07/18 13:22:26 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*get_num_tk(t_data *data, char *input, size_t start_idx)
{
	size_t	i;

	i = start_idx;
	while (ft_isdigit(input[i]))
		i++;
	return (get_token(data, ft_substr(input, start_idx, i - start_idx),
			NULL, TK_NUMBER));
}

t_token	*get_string_tk(t_data *data, char *input, size_t *start_idx)
{
	size_t			i;
	unsigned char	quote;
	t_token			*str_tk;

	i = *start_idx + 1;
	quote = input[*start_idx];
	while (input[i] && input[i] != quote)
		i++;
	str_tk = get_token(data, ft_substr(input, *start_idx + 1,
				i - *start_idx - 1), NULL, TK_STRING);
	*start_idx += 2;
	return (str_tk);
}

t_token	*get_word_tk(t_data *data, char *input, size_t start_idx)
{
	char	*word;

	word = get_substr(input, start_idx);
	if (!word || !word[0])
	{
		if (word)
			free(word);
		return (NULL);
	}
	return (get_token(data, word, NULL, TK_WORD));
}

t_token	*get_flag_tk(t_data *data, char *input, size_t start_idx)
{
	char	*lexstr;

	lexstr = get_substr(input, start_idx);
	if (!lexstr)
		return (get_token(data, NULL, NULL, TK_INVALID));
	return (get_token(data, lexstr, NULL, TK_FLAG));
}
