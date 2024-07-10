/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_retrieve_tk1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 08:04:48 by bento             #+#    #+#             */
/*   Updated: 2024/07/10 14:05:31 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*get_num_tk(t_data *data, char *input, size_t start_idx)
{
	size_t	i;

	i = start_idx;
	while (ft_isdigit(input[i]))
		i++;
	return (get_token(data, ft_substr(input, start_idx, i - start_idx), TK_NUMBER));
}

t_token	*get_string_tk(t_data *data, char *input, size_t start_idx)
{
	size_t			i;
	char			*lexstr;
	unsigned char	quote;

	i = start_idx + 1;
	quote = input[start_idx];
	while (input[i] && input[i] != quote)
		i++;
	lexstr = ft_substr(input, start_idx, i - start_idx + 1);
	return (get_token(data, lexstr, TK_STRING));
}

t_token	*get_word_tk(t_data *data, char *input, size_t start_idx)
{
	return (get_token(data, get_substr(input, start_idx), TK_WORD));
}

t_token	*get_flag_tk(t_data *data, char *input, size_t start_idx)
{
	char	*lexstr;
	size_t	i;

	i = start_idx;
	if (input[i + 1] == 'n' && (is_space(input[i + 2]))
		|| input[i + 1] == 0)
		return (get_token(data, ft_strdup("-n"), TK_FLAG));
	return (get_token(data, NULL, TK_INVALID));
}
