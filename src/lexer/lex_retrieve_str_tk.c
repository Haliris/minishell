/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_retrieve_str_tk.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:40:12 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/25 17:47:11 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_token	*get_doll_str_tk(t_data *data, char *input, size_t *start_idx)
{
	char	*outstr;

	outstr = ft_substr(input, *start_idx, 2);
	(*start_idx) += 2;
	if (!outstr)
		return (NULL);
	return (get_token(data, outstr, NULL, TK_STRING));
}

static void	extract_str(t_data *data, size_t *startidx,
	size_t size, t_token *tk)
{
	size_t	i;
	bool	in_quote;
	char	*outstr;

	outstr = (char *)ft_calloc(size + 1, 1);
	if (!outstr)
		return ;
	i = 0;
	tk->quote = 0;
	in_quote = (in(data->input[*startidx], "\"\'"));
	if (in_quote)
		tk->quote = data->input[(*startidx)++];
	while (data->input[*startidx])
	{
		if (in_quote && data->input[*startidx] == tk->quote)
			break ;
		if (!in_quote && is_delim(data->input[*startidx]))
			break ;
		(outstr)[i++] = data->input[(*startidx)++];
	}
	if (in_quote)
		(*startidx)++;
	tk->lexstr = outstr;
}

t_token	*get_string_tk(t_data *data, size_t *start_idx)
{
	t_token		*str_tk;
	size_t		token_size;

	if (data->input[*start_idx] == '$' && data->input[(*start_idx) + 1]
		&& in(data->input[(*start_idx) + 1], ":/,.~^="))
		return (get_doll_str_tk(data, data->input, start_idx));
	token_size = get_str_tk_len(data->input, *start_idx);
	if (!token_size)
		return (NULL);
	str_tk = get_token(data, NULL, NULL, TK_STRING);
	if (!str_tk)
		return (NULL);
	str_tk->startidx = *start_idx;
	extract_str(data, start_idx, token_size, str_tk);
	str_tk->endidx = *start_idx;
	return (str_tk);
}
