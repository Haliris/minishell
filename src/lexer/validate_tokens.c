/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:26:40 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/18 13:24:19 by bthomas          ###   ########.fr       */
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
		if (token->type == TK_REDIR && (!next || !token->prev))
			return (true);
		token = next;
	}
	return (false);
}

/* "cd with only a relative or absolute path" */
static bool	is_invalid_cd(t_token *token)
{
	t_token	*next;

	while (token)
	{
		if (token->type == TK_BUILTIN
			&& ft_strncmp(token->lexstr, "cd", 2) == 0)
		{
			next = token->next;
			if (!next || !next->lexstr)
				return (true);
			if (next->lexstr[0] == '-')
				return (true);
		}
		token = token->next;
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
bool	invalid_tokens(t_token *token)
{
	return (detect_executables(token)
		|| invalid_tk_exists(token)
		|| is_orphaned_op(token)
		|| is_invalid_cd(token));
}
