/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:26:40 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/28 14:20:35 by bthomas          ###   ########.fr       */
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
		if (!token->lexstr)
			return (true);
		token = token->next;
	}
	return (false);
}

/* Add in orphan operators check, e.g., nothing before pipe */
static bool	is_orphaned_op(t_token *token)
{
	t_token	*next;
	bool	is_echo;

	is_echo = false;
	while (token)
	{
		next = token->next;
		if (token->type == TK_PIPE || token->type == TK_REDIR)
			is_echo = false;
		if (token->type == TK_BUILTIN && ft_strcmp("echo", token->lexstr) == 0)
			is_echo = true;
		if (token->type == TK_PIPE && (!token->prev || !token->next))
			return (true);
		if (token->type == TK_OPERATOR && !next && !is_echo)
			return (true);
		if (token->type == TK_REDIR && (!next))
			return (true);
		if (token->type == TK_PATH && !token->path)
			return (true);
		token = next;
	}
	return (false);
}

static bool	space_within_lexstr(t_token *token)
{
	size_t	i;

	i = 0;
	while (token->lexstr && token->lexstr[i])
	{
		if (is_space(token->lexstr[i]))
			return (true);
		i++;
	}
	return (false);
}

static void	detect_executables(t_data *data)
{
	t_token	*curr_tk;

	curr_tk = data->token;
	while (curr_tk)
	{
		if (curr_tk->type == TK_EXITSTATUS)
			expand_string_var(data, &curr_tk->lexstr);
		if (is_builtin(curr_tk->lexstr, 0))
			curr_tk->type = TK_BUILTIN;
		else if (curr_tk->type == TK_STRING && !space_within_lexstr(curr_tk)
			&& is_executable(data, curr_tk->lexstr, 0))
		{
			curr_tk->path = get_exec_path(data, curr_tk->lexstr, 0);
			if (curr_tk->path)
				curr_tk->type = TK_EXECUTABLE;
		}
		if (curr_tk->type == TK_PATH && !curr_tk->path)
			curr_tk->path = ft_strdup("");
		curr_tk = curr_tk->next;
	}
}

/* bultins with invalid flags */
bool	invalid_tokens(t_data *data)
{
	t_token	*token;
	bool	ret;

	token = data->token;
	detect_executables(data);
	ret = (invalid_tk_exists(token)
			|| is_orphaned_op(token));
	return (ret);
}
