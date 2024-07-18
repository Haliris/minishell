/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:26:40 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/17 19:24:34 by jteissie         ###   ########.fr       */
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

static void	expand_str_tks(t_data *data, t_token *token)
{
	while (token)
	{
		if (token->type == TK_STRING && var_in_str(token->lexstr))
			expand_string_var(data, &token->lexstr);
		token = token->next;
	}
}

/* bultins with invalid flags */
bool	invalid_tokens(t_data *data, t_token *token)
{
	expand_str_tks(data, token);
	return (invalid_tk_exists(token)
		|| is_orphaned_op(token)
		|| is_invalid_cd(token));
}
