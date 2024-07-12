/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_redirect_table.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:21:54 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/12 18:53:50 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_redir_type(t_token *lexer)
{
	if (ft_strncmp(lexer->lexstr, "<", 1) == 0)
		return (TK_PARS_IN);
	else if (ft_strncmp(lexer->lexstr, ">", 1) == 0)
		return (TK_PARS_OUT);
	else if (ft_strncmp(lexer->lexstr, ">>", 1) == 0)
		return (TK_PARS_OUT_APPEND);
	return (TK_INVALID);
}

int	build_redirect_table(t_lex_parser *parsed, t_token *lexer)
{
	t_redirect_table	*redir_table;

	redir_table = ft_calloc(1, sizeof(t_redirect_table));
	if (!redir_table)
		return (PANIC);
	redir_table->redir_str = lexer->next->lexstr;
	redir_table->type = get_redir_type(lexer);
	lexer->next->type = TK_RESERVED;
	lexer->type = TK_RESERVED;
	if (parsed_add_back(parsed, redir_table, TK_PARS_REDIR) == PANIC)
		return (PANIC);
	return (SUCCESS);
}
