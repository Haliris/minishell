/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:52:36 by bento             #+#    #+#             */
/*   Updated: 2024/07/28 16:49:08 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	replace_str(char **old, char *new)
{
	if (!old || !*old)
		return ;
	if (*old)
		free(*old);
	*old = new;
}

char	*get_substr(char *input, size_t start_idx)
{
	char	*substr;
	size_t	i;

	i = start_idx;
	while (input[i] && !is_delim(input[i], false))
		i++;
	if (i == start_idx)
		return (NULL);
	substr = ft_substr(input, start_idx, i - start_idx);
	if (!substr)
		return (NULL);
	return (substr);
}

bool	in_echo(t_token *tk)
{
	t_token	*prev;

	if (!tk)
		return (false);
	while (tk)
	{
		prev = tk->prev;
		if (tk->type == TK_PIPE || tk->type == TK_REDIR
			|| tk->type == TK_HEREDOC)
			return (false);
		if (ft_strcmp("echo", tk->lexstr) == 0
			&& (!prev || !prev->prev || (prev->prev->type == TK_PIPE
					|| prev->prev->type == TK_REDIR
					|| prev->prev->type == TK_HEREDOC)))
			return (true);
		tk = prev;
	}
	return (false);
}

/* problem chars: & | < > ; ( ) \ " '
	but, bash allows them */
void	remove_lim_node(t_token *node)
{
	if (node->prev && node->next)
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	else if (node->prev)
		node->prev->next = node->next;
	else if (node->next)
		node->next->prev = node->prev;
	if (node->lexstr)
		free(node->lexstr);
	free(node);
}

bool	space_within_lexstr(t_token *token)
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
