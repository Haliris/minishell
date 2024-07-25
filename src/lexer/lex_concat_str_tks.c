/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_concat_str_tks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:30:33 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/25 17:53:09 by bthomas          ###   ########.fr       */
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
		if (curr_tk == TK_STRING && curr_tk->quote != '\'')
		{
			if (var_in_str(curr_tk))
				expand_string_var(data, &curr_tk->lexstr);
		}
		curr_tk = curr_tk->next;
	}
	return ;
}

static int	concat_prev_tk(t_token *tk)
{
	return (0);
}

int	concatenate_str_tks(t_data *data)
{
	t_token	*curr_tk;

	if (!data->token)
		return (0);
	expand_all_vars(data);
	curr_tk = data->token->next;
	while (curr_tk)
	{
		if (curr_tk->type == TK_STRING && curr_tk->prev == TK_STRING)
		{
			if (!is_space(data->input[curr_tk->prev->endidx]))
				if (concat_prev_tk(curr_tk))
					return (PANIC);
		}
		curr_tk = curr_tk->next;
	}
	return (0);
}
