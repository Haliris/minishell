/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_retrieve_tk1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 08:04:48 by bento             #+#    #+#             */
/*   Updated: 2024/07/17 19:27:53 by jteissie         ###   ########.fr       */
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

t_token	*get_string_tk(t_data *data, char *input, size_t start_idx)
{
	size_t			i;
	unsigned char	quote;

	i = start_idx + 1;
	quote = input[start_idx];
	while (input[i] && input[i] != quote)
		i++;
	return (get_token(data, ft_substr(input, start_idx, i - start_idx + 1),
			NULL, TK_STRING));
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
