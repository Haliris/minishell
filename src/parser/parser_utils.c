/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:00:24 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/10 15:18:13 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_invalid_token(t_token *tokens)
{
	t_token	*roaming;

	roaming = tokens;
	while (roaming)
	{
		if (roaming->type == TK_INVALID)
			return (TRUE);
		roaming = roaming->next;
	}
	return (FALSE);
}

void	reserve_token(t_token *tokens)
{
	t_token	*roaming;

	roaming = tokens;
	while (roaming->prev)
		roaming = roaming->prev;
	while (roaming)
	{
		if (roaming->type == TK_MARKED)
			roaming->type = TK_RESERVED;
		roaming = roaming->next;
	}
}

int	check_remaining_tokens(t_token *tokens)
{
	int		remaining;
	t_token	*roaming;

	remaining = 0;
	roaming = tokens;
	while (roaming)
	{
		if (roaming->type != TK_RESERVED)
			remaining++;
		roaming = roaming->next;
	}
	return (remaining);
}

char	*re_join_lexstr(char *s1, char *lexstr, int mode)
{
	char	*temp_new;
	char	*new;

	if (!s1)
		return (lexstr);
	if (!lexstr)
		return (s1);
	if (mode == FORWARD)
		temp_new = ft_strjoin(s1, " ");
	else
		temp_new = ft_strjoin(" ", s1);
	if (!temp_new)
		return (free(s1), NULL);
	if (mode == FORWARD)
		new = ft_strjoin(temp_new, lexstr);
	else
		new = ft_strjoin(lexstr, temp_new);
	free(s1);
	free(temp_new);
	if (!new)
		return (NULL);
	return (new);
}

int	parsed_add_back(t_lex_parser *parsed, void *table, int type)
{
	t_lex_parser	*last;
	t_lex_parser	*new_node;

	if (!parsed->type)
	{
		parsed->table = table;
		parsed->type = type;
		return ;
	}
	new_node = ft_calloc(1, sizeof(t_lex_parser));
	if (!new_node)
		return (PANIC);
	new_node->table = table;
	new_node->type = type;
	new_node->next = NULL;
	last = parsed;
	while (last->next)
		last = last->next;
	last->next = new_node;
	new_node->prev = last;
	return (SUCCESS);
}
