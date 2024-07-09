/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_redirect_table.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:21:54 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/09 14:03:25 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_dummy.h"

int	get_redir_type(t_token *lexer)
{
	if (lexer->type = TK_IN)
		return (TK_IN);
	else if (lexer->type = TK_OUT)
		return (TK_OUT);
	else if (lexer->type == TK_OUT_APPEND)
		return (TK_OUT_APPEND);
}

int	build_redirect_table(t_lex_parser *parsed, t_token *lexer) // to adapt for infile or outfile
{
	t_redirect_table	*redir_table;

	if (check_parsing_error(lexer, TK_REDIR) == TRUE)
		return (PANIC);
	redir_table = ft_calloc(1, sizeof(t_redirect_table));
	if (!redir_table)
		return (PANIC);
	redir_table->redir_str = lexer->next->lexstr;
	redir_table->type = get_redir_type(lexer);
	lexer->next->type = TK_RESERVED;
	lexer->type = TK_RESERVED;
	if (parsed_table_add_back(parsed, redir_table, TK_REDIR) == PANIC) //TK_INFILE IS WRONG HERE
		return (PANIC);
	return (SUCCESS);
}
