/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_concat_str_tks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:30:33 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/25 18:47:30 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
		if (var_in_str(curr_tk))
			expand_string_var(data, &curr_tk->lexstr);
*/
static void	expand_all_vars(t_data *data)
{
	t_token	*curr_tk;

	curr_tk = data->token;
	while (curr_tk)
	{
		if (curr_tk->type == TK_STRING && curr_tk->quote == '\"')
		{
			if (var_in_str(curr_tk))
				expand_string_var(data, &curr_tk->lexstr);
		}
		curr_tk = curr_tk->next;
	}
	return ;
}

void	free_tk(t_token *tk)
{
	if (tk->lexstr)
	{
		free(tk->lexstr);
		tk->lexstr = NULL;
	}
	if (tk->path)
	{
		free(tk->path);
		tk->path = NULL;
	}
	free(tk);
	tk = NULL;
}

static void	replace_tk(t_data *data, t_token **tk, t_token *prev,
	t_token *replacement)
{
	replacement->prev = prev->prev;
	replacement->next = (*tk)->next;
	if (replacement->prev)
		replacement->prev->next = replacement;
	if (replacement->next)
		replacement->next->prev = replacement;
	if (!prev->prev)
		data->token = replacement;
	free_tk(prev);
	free_tk(*tk);
	*tk = replacement;
}

static int	concat_prev_tk(t_data *data, t_token **tk)
{
	t_token	*prev;
	t_token	*replacement;
	char	*replace_str;

	replacement = get_token(data, NULL, NULL, TK_STRING);
	if (!replacement)
		return (PANIC);
	prev = (*tk)->prev;
	replace_str = ft_strjoin(prev->lexstr, (*tk)->lexstr);
	if (!replace_str)
	{
		free(replacement);
		return (PANIC);
	}
	replacement->lexstr = replace_str;
	replace_tk(data, tk, prev, replacement);
	return (0);
}

int	concatenate_str_tks(t_data *data)
{
	t_token	*curr_tk;

	if (!data->token || !data->token->lexstr)
		return (0);
	expand_all_vars(data);
	curr_tk = data->token->next;
	while (curr_tk)
	{
		if (curr_tk->startidx
			&& !is_delim(data->input[curr_tk->startidx - 1]))
			if (concat_prev_tk(data, &curr_tk))
				return (PANIC);
		curr_tk = curr_tk->next;
	}
	return (0);
}
