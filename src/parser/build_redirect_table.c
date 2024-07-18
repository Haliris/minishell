/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_redirect_table.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:21:54 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/18 12:55:40 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_redir_type(t_token *lexer)
{
	if (lexer->type == TK_HEREDOC)
		return (TK_PARS_HEREDOC);
	else if (ft_strncmp(lexer->lexstr, "<", 1) == 0)
		return (TK_PARS_IN);
	else if (ft_strncmp(lexer->lexstr, ">>", 2) == 0)
		return (TK_PARS_APPEND);
	else if (ft_strncmp(lexer->lexstr, ">", 1) == 0)
		return (TK_PARS_OUT);
	return (TK_PARS_NULL);
}

int	build_redirect_table(t_parser *parsed, t_token *lexer)
{
	t_redirect_table	*redir_table;

	redir_table = ft_calloc(1, sizeof(t_redirect_table));
	if (!redir_table)
		return (PANIC);
	redir_table->redir_str = NULL;
	redir_table->heredoc = TRUE;
	if (lexer->type == TK_HEREDOC)
		redir_table->redir_str = lexer->heredoc->path;
	else
	{
		redir_table->redir_str = ft_strdup(lexer->next->lexstr);
		if (!redir_table->redir_str)
			return (PANIC);
		redir_table->heredoc = FALSE;
		lexer->next->type = TK_RESERVED;
	}
	redir_table->type = get_redir_type(lexer);
	lexer->type = TK_RESERVED;
	if (parsed_add_back(parsed, redir_table, TK_PARS_REDIR) == PANIC)
		return (PANIC);
	return (SUCCESS);
}
