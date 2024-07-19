/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:26:40 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/19 17:50:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

bool	invalid_tk_exists(t_token *token)
{
	while (token)
	{
		if (token->type == TK_INVALID)
			return (true);
		if (token->type == TK_HEREDOC && !token->heredoc)
			return (true);
		token = token->next;
	}
	return (false);
}

/* Add in orphan operators check, e.g., nothing before pipe */
static bool	is_orphaned_op(t_token *token)
{
	t_token	*next;

	while (token)
	{
		next = token->next;
		if (token->type == TK_PIPE && !token->prev)
			return (true);
		if (token->type == TK_OPERATOR && !next)
			return (true);
		if (token->type == TK_REDIR && (!next))
			return (true);
		token = next;
	}
	return (false);
}

static int	detect_executables(t_token *token)
{
	t_token	*curr_tk;

	curr_tk = token;
	while (curr_tk)
	{
		if (curr_tk->type == TK_STRING && is_executable(curr_tk->lexstr, 0))
		{
			curr_tk->path = get_exec_path(curr_tk->lexstr, 0);
			if (!curr_tk->path)
				return (PANIC);
			curr_tk->type = TK_EXECUTABLE;
		}
		curr_tk = curr_tk->next;
	}
	return (0);
}

/* bultins with invalid flags */
bool	invalid_tokens(t_data *data)
{
	t_token	*token;
	bool	ret;

	token = data->token;
	ret = (detect_executables(token)
			|| invalid_tk_exists(token)
			|| is_orphaned_op(token));
	if (ret)
		free_lexmem(data);
	return (ret);
}
