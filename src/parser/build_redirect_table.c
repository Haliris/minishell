/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_redirect_table.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:21:54 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/08 18:22:23 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_dummy.h"

void	build_redirect_table(t_lex_parser *parsed, t_token *lexer) // to adapt for infile or outfile
{
	t_redirect_table	*redir_table;

	if (!lexer->next)
		return ;
	redir_table = ft_calloc(1, sizeof(t_redirect_table));
	if (!redir_table)
		return ;
	redir_table->redir_str = lexer->next->lexstr;
	lexer->next->type = TK_RESERVED;
	lexer->type = TK_RESERVED;
	parsed_table_add_back(parsed, redir_table, TK_INFILE); //TK_INFILE IS WRONG HERE
}
