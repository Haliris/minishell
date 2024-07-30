/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_retrieve_str_tk.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:40:12 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/30 11:06:28 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*get_doll_str_tk(t_data *data, char *input, size_t *start_idx)
{
	t_token	*doll_tk;
	char	*outstr;

	outstr = ft_substr(input, *start_idx, 2);
	if (!outstr)
		return (NULL);
	doll_tk = get_token(data, outstr, NULL, TK_STRING);
	if (!doll_tk)
		return (NULL);
	doll_tk->startidx = *start_idx;
	(*start_idx) += 2;
	return (doll_tk);
}

static size_t	get_word_len(t_data *data, size_t startidx, bool echo_str)
{
	size_t	len;
	size_t	i;
	char	quote;
	bool	in_quote;

	len = 0;
	i = startidx;
	in_quote = in(data->input[i], "\'\"");
	quote = 0;
	if (in_quote)
		quote = data->input[i++];
	while (data->input[i])
	{
		if ((!in_quote && in(data->input[i], "\'\""))
			|| (in_quote && data->input[i] == quote)
			|| (!in_quote && is_delim(data->input[i], echo_str)))
			break ;
		else
			len++;
		i++;
	}
	return (len);
}

static char	*extract_word(t_data *data, size_t *startidx, bool echo_str)
{
	size_t	i;
	bool	in_quote;
	char	quote;
	char	*word;

	i = 0;
	word = (char *)ft_calloc(get_word_len(data, *startidx, echo_str) + 1, 1);
	if (!word)
		return (NULL);
	in_quote = in(data->input[*startidx], "\'\"");
	quote = 0;
	if (in_quote)
		quote = data->input[(*startidx)++];
	while (data->input[*startidx])
	{
		if ((!in_quote && in(data->input[*startidx], "\'\""))
			|| (in_quote && data->input[*startidx] == quote)
			|| (!in_quote && is_delim(data->input[*startidx], echo_str)))
			break ;
		else
			word[i++] = data->input[(*startidx)++];
	}
	if (in_quote)
		(*startidx)++;
	return (word);
}

static void	get_all_words(t_data *data, size_t *startidx, t_token *tk,
	bool echo_str)
{
	char	quote;
	char	*word;
	size_t	old_idx;

	quote = 0;
	while (data->input[(*startidx)])
	{
		if (in(data->input[*startidx], "\'\""))
			quote = data->input[*startidx];
		else
			quote = 0;
		old_idx = *startidx;
		word = extract_word(data, startidx, echo_str);
		if (old_idx == *startidx)
		{
			if (word)
				free(word);
			return ;
		}
		if (var_in_str(word, quote))
			expand_string_var(data, &word);
		tk->lexstr = ft_strreplacejoin(&tk->lexstr, &word);
		if (is_space(data->input[(*startidx)]))
			break ;
	}
}

t_token	*get_string_tk(t_data *data, size_t *start_idx)
{
	t_token		*str_tk;
	bool		echo_str;

	echo_str = in_builtin(lex_get_last_token(data), "echo");
	str_tk = get_token(data, NULL, NULL, TK_STRING);
	if (!str_tk)
		return (NULL);
	str_tk->startidx = *start_idx;
	get_all_words(data, start_idx, str_tk, echo_str);
	str_tk->endidx = *start_idx;
	return (str_tk);
}
