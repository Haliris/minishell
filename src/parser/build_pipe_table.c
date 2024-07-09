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

	r = lexer;
	while (r && r->type != TK_RESERVED)
	{
		if (r->next->type != TK_PIPE)
		{
			r->lexstr = re_join_lexstr(r->next->lexstr, r->lexstr, BACKWARD);
			if (!r->lexstr)
				return (PANIC);
		}
		if (r->type == TK_EXECUTABLE)
		{
			r->type = TK_MARKED;
			break ;
		}
		r->type = TK_MARKED;
		r = r->prev;
	}
	return (SUCCESS);
}

int	build_cmd2_str(t_token *lexer)
{
	t_token	*r;

	r = lexer;
	if (r->type != TK_EXECUTABLE)
		return (PANIC);
	r->type = TK_MARKED;
	r = r->next;
	while (r && r->type == TK_STRING)
	{
		r->lexstr = re_join_lexstr(r->prev->lexstr, r->lexstr, FORWARD);
		if (!r->lexstr)
			return (PANIC);
		r->type = TK_MARKED;
		r = r->next;
	}
	return (SUCCESS);
}

char	*get_cmd_lexstr(t_token *tokens, int mode)
{
	t_token	*roaming;

	roaming = tokens;
	if (mode == FORWARD)
		while (roaming->next && roaming->next->type == TK_MARKED)
			roaming = roaming->next;
	else
		while (roaming->prev && roaming->prev->type == TK_MARKED)
			roaming = roaming->prev;
	return (roaming->lexstr);
}

int	build_pipe_table(t_lex_parser *parsed, t_token *lexer)
{
	t_pipe_table	*pipe_table;

	if (check_parsing_error(lexer, TK_PIPE) == TRUE)
		return (PANIC);
	if (build_cmd1_str(lexer) == PANIC || build_cmd2_str(lexer) == PANIC)
		return (PANIC);
	pipe_table = ft_calloc(1, sizeof(t_pipe_table));
	if (!pipe_table)
		return (PANIC);
	pipe_table->cmd1 = get_cmd_lexstr(lexer, BACKWARD);
	pipe_table->cmd2 = get_cmd_lexstr(lexer, FORWARD);
	parsed_add_back(parsed, pipe_table, TK_PIPE);
	lexer->type = TK_MARKED;
	reserve_token(lexer);
	return (SUCCESS);
}
