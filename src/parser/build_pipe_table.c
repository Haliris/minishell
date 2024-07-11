/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_pipe_table.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:23:53 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/09 15:23:53 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	build_cmd1_str(t_token *lexer)
{
	t_token	*r;
	char	*cmd_str;

	r = lexer;
	cmd_str = NULL;
	while (r->type != TK_PARS_PIPE)
	{
		if (r->type == TK_STRING)
		{
			cmd_str = re_join_lexstr(cmd_str, r->lexstr, BACKWARD);
			if (!cmd_str)
				return (PANIC);
			r->type = TK_MARKED;
			free(r->lexstr);
			r->lexstr = cmd_str;
		}
		if (!r->prev)
			break ;
		r = r->prev;
	}
	return (SUCCESS);
}

int	build_cmd2_str(t_token *lexer)
{
	t_token	*r;
	char	*cmd_str;

	r = lexer;
	cmd_str = NULL;
	while (r->type != TK_PARS_PIPE)
	{
		if (r->type == TK_STRING)
		{
			cmd_str = re_join_lexstr(cmd_str, r->lexstr, FORWARD);
			if (!cmd_str)
				return (PANIC);
			r->type = TK_MARKED;
			free(r->lexstr);
			r->lexstr = cmd_str;
		}
		if (!r->next)
			break ;
		r = r->next;
	}
	return (SUCCESS);
}

int	build_pipe_table(t_lex_parser *parsed, t_token *lexer)
{
	t_pipe_table	*pipe_table;

	pipe_table->cmd1 = NULL;
	pipe_table->cmd2 = NULL;
	if (check_parsing_error(lexer, TK_PARS_PIPE) == TRUE)
		return (PANIC);
	if (build_cmd1_str(lexer) == PANIC || build_cmd2_str(lexer) == PANIC)
		return (PANIC);
	pipe_table = ft_calloc(1, sizeof(t_pipe_table));
	if (!pipe_table)
		return (PANIC);
	pipe_table->cmd1 = get_cmd_pipe(lexer, BACKWARD, parsed);
	pipe_table->cmd2 = get_cmd_pipe(lexer, FORWARD, parsed);
	parsed_add_back(parsed, pipe_table, TK_PIPE);
	lexer->type = TK_MARKED;
	reserve_token(lexer);
	return (SUCCESS);
}
