/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:00:24 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/05 15:24:12 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_dummy.h"
#include "parser.h"

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

void	remove_token(t_token *tokens)
{
	if (!tokens)
		return ; //wtf call, should not happen
	if (tokens->prev)
		tokens->prev->next = tokens->next;
	if (tokens->next)
		tokens->next->prev = tokens->prev;
	free(tokens);
}

void	parsed_table_add_back(t_lex_parser *parsed, void *table, int type)
{
	t_lex_parser	*last;
	t_lex_parser	*new_node;

	new_node = ft_calloc(1, sizeof(t_lex_parser));
	if (!new_node)
		return ;
	new_node->table = table;
	new_node->type = type;
	new_node->next = NULL;
	last = parsed;
	while (last->next)
		last = last->next;
	last->next = new_node;
}