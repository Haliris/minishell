/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_retrieve_tk1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 08:04:48 by bento             #+#    #+#             */
/*   Updated: 2024/07/20 16:57:32 by bthomas          ###   ########.fr       */
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

void	get_extended_str(char *input, size_t *startidx,
	char **outstr, size_t str_tk_len)
{
	bool	in_quote;
	char	quote;
	size_t	i;

	i = 0;
	in_quote = false;
	quote = 0;
	while (input[*startidx] && i < str_tk_len)
	{
		if (!in_quote && in(input[*startidx], "\'\""))
		{
			in_quote = true;
			quote = input[*startidx];
		}
		else if (in_quote && input[*startidx] == quote)
			in_quote = false;
		else if (!in_quote && is_delim(input[*startidx]))
		{
			(*startidx)++;
			break ;
		}
		else
			(*outstr)[i++] = input[*startidx];
		(*startidx)++;
	}
}

static void	process_empty_str(char **outstr)
{
	size_t	i;
	char	*replacement_str;

	i = 0;
	while (*outstr && (*outstr)[i])
	{
		if (!is_space((*outstr)[i]))
			return ;
		i++;
	}
	replacement_str = ft_strjoin3("\'", *outstr, "\'");
	if (!replacement_str)
		return ;
	replace_str(outstr, replacement_str);
}

t_token	*get_string_tk(t_data *data, char *input, size_t *start_idx)
{
	t_token		*str_tk;
	size_t		token_size;
	char		*outstr;

	token_size = get_str_tk_len(input, *start_idx);
	if (!token_size)
		return (NULL);
	outstr = (char *)ft_calloc(token_size + 1, 1);
	if (!outstr)
		return (NULL);
	get_extended_str(input, start_idx, &outstr, token_size);
	if (!*outstr)
	{
		free(outstr);
		return (NULL);
	}
	process_empty_str(&outstr);
	str_tk = get_token(data, outstr, NULL, TK_STRING);
	if (!str_tk)
		free(outstr);
	return (str_tk);
}

t_token	*get_flag_tk(t_data *data, char *input, size_t start_idx)
{
	char	*lexstr;

	lexstr = get_substr(input, start_idx);
	if (!lexstr)
		return (get_token(data, NULL, NULL, TK_INVALID));
	return (get_token(data, lexstr, NULL, TK_FLAG));
}
