/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:48:06 by bento             #+#    #+#             */
/*   Updated: 2024/07/22 14:29:16 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	skip_invalid_chars(t_data *data, size_t input_len, size_t *i)
{
	char	*input;

	input = data->input;
	while (*i < input_len)
	{
		if (is_space(input[*i]))
		{
			while (is_space(input[*i]))
				(*i)++;
		}
		else if (empty_quote(data->input, *i))
		{
			while (empty_quote(data->input, *i))
				(*i) += 2;
		}
		else if (input[*i] == '$' && input[(*i) + 1]
			&& !in(input[(*i) + 1], "$?")
			&& !is_space(input[(*i) + 1])
			&& (!ft_isalpha(input[(*i) + 1])
				&& !in(input[(*i) + 1], ":/,.~^=_")))
			(*i) += 1 + (1 * (!in(input[(*i) + 1], "\"\'")));
		else
			return ;
	}
}

static t_token	*build_tokenlist2(t_data *data, size_t *i)
{
	t_token	*curr_tk;

	curr_tk = NULL;
	if (in(data->input[*i], "<>"))
		curr_tk = get_redir_tk(data, data->input, *i);
	else if (is_builtin(data->input, *i))
		curr_tk = get_token(data, get_substr(data->input, *i),
				NULL, TK_BUILTIN);
	else if (data->input[*i] == '=')
		curr_tk = get_token(data, ft_strdup("="),
				NULL, TK_OPERATOR);
	else if (is_executable(data->input, *i))
		curr_tk = get_exec_tk(data, data->input, *i);
	else if (data->input[*i] == '$' && data->input[(*i) + 1] == '$')
		curr_tk = get_path_tk(data, data->input, *i);
	else if (data->input[*i] == '$'
		&& (!data->input[*i + 1] || is_space(data->input[*i + 1])))
		curr_tk = get_token(data, ft_strdup("$"), NULL, TK_NUMBER);
	else if (data->input[*i] == '$' && data->input[*i + 1] == '?')
		curr_tk = get_token(data, ft_strdup("$?"), NULL, TK_EXITSTATUS);
	else if (data->input[*i] == '$' && data->input[*i + 1])
		curr_tk = get_path_tk(data, data->input, *i);
	else
		curr_tk = get_string_tk(data, data->input, i);
	return (curr_tk);
}

/* Need to split this in 2 or 3 functions */
static int	build_tokenlist1(t_data *data, size_t input_len)
{
	size_t	i;
	t_token	*curr_tk;

	curr_tk = NULL;
	i = 0;
	while (i < input_len)
	{
		if (is_invalid_export(data, i))
			return (PANIC);
		skip_invalid_chars(data, input_len, &i);
		if (i >= input_len)
			break ;
		if ((data->input[i] == '\"' || data->input[i] == '\'')
			|| (data->input[i] == '$' && in(data->input[i + 1], ":/,.~^=")))
			curr_tk = get_string_tk(data, data->input, &i);
		else if (data->input[i] == '|')
			curr_tk = get_token(data, ft_strdup("|"), NULL, TK_PIPE);
		else
			curr_tk = build_tokenlist2(data, &i);
		if (!curr_tk || !curr_tk->lexstr)
			return (1);
		i += ft_strlen(curr_tk->lexstr) * (curr_tk->type != TK_STRING);
		lex_add_token(data, curr_tk);
	}
	return (0);
}

int	build_heredocs(t_data *data)
{
	t_token	*roaming;

	roaming = data->token;
	while (roaming)
	{
		if (roaming->type == TK_REDIR && ft_strcmp(roaming->lexstr, "<<") == 0)
		{
			if (get_heredoc_tk(roaming, data) == PANIC)
				return (PANIC);
			if (roaming->type == TK_INVALID)
				return (PANIC);
		}
		roaming = roaming->next;
	}
	return (SUCCESS);
}

/* Unfortunately we're not allowed to use case statmements :( */
int	lexer(t_data *data)
{
	size_t	input_len;

	input_len = ft_strlen(data->input);
	if (build_tokenlist1(data, input_len))
		return (1);
	if (invalid_tokens(data))
		return (1);
	if (build_heredocs(data) == PANIC)
	{
		unlink_heredocs(data);
		return (1);
	}
	return (0);
}
