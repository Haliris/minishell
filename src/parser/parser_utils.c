/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:00:24 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/15 12:59:27 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	panic(t_lex_parser *parsed)
{
	(void)parsed;
	ft_putstr_fd("free my parsed linked list please\n", STDERR_FILENO);
	ft_putstr_fd("probably exit the process too\n", STDERR_FILENO);
}

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

int	parsed_add_back(t_lex_parser *p, void *t, t_parsed_token type)
{
	t_lex_parser	*last;
	t_lex_parser	*new_node;

	if (p->type == TK_PARS_NULL)
	{
		p->table = t;
		p->type = type;
		return (SUCCESS);
	}
	new_node = ft_calloc(1, sizeof(t_lex_parser));
	if (!new_node)
		return (PANIC);
	new_node->table = t;
	new_node->type = type;
	new_node->next = NULL;
	last = p;
	while (last->next)
		last = last->next;
	last->next = new_node;
	new_node->prev = last;
	return (SUCCESS);
}
