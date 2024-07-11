/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:21:33 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/11 13:41:21 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	panic(t_lex_parser *parsed)
{
	(void)parsed;
	ft_putstr_fd("free my parsed linked list please\n", STDERR_FILENO);
	ft_putstr_fd("probably exit the process too\n", STDERR_FILENO);
}

char	*make_cmd_buffer(t_token *roaming)
{
	char	*cmd_buff;

	cmd_buff = NULL;
	while (roaming && roaming->type != TK_PIPE)
	{
		if (roaming->type != TK_RESERVED)
		{
			if (cmd_buff)
				cmd_buff = re_join_lexstr(cmd_buff, roaming->lexstr, FORWARD);
			else
				cmd_buff = roaming->lexstr;
			roaming->type = TK_RESERVED;
		}
		roaming = roaming->next;
	}
	return (NULL);
}

void	parse_command(t_lex_parser *parsed, t_token *tokens)
{
	t_token		*r;
	t_cmd_table	*table;
	char		*cmd_buffer;

	table = ft_calloc(1, sizeof(t_cmd_table));
	if (!table)
		return ;
	cmd_buffer = NULL;
	r = tokens;
	while (r && r->prev != TK_PIPE)
		r = r->prev;
	table->cmd = make_cmd_buffer(r);
	if (table->cmd)
		parsed_add_back(parsed, table, TK_CMD);
	else
		free(table);
}

void	parse_operators(t_lex_parser *parsed, t_token *tokens)
{
	t_token	*roaming;

	roaming = tokens;
	while (roaming)
	{
		while (roaming && roaming->type != TK_PIPE)
		{
			if (roaming->type == TK_REDIR)
				if (build_redirect_table(parsed, roaming) == PANIC)
					panic(parsed);
			roaming = roaming->next;
		}
		parse_command(parsed, tokens);
		if (roaming && roaming->type == TK_PIPE)
			parsed_add_back(parsed, NULL, TK_PIPE);
		roaming = roaming->next;
	}
}

t_lex_parser	*interprete_lexer(t_token *tokens_list)
{
	t_lex_parser	*parsed_lex;

	if (check_invalid_token(tokens_list))
		return (NULL);
	parsed_lex = ft_calloc(1, sizeof(t_lex_parser));
	if (!parsed_lex)
		return (NULL);
	parsed_lex->next = NULL;
	parsed_lex->prev = NULL;
	parse_operators(parsed_lex, tokens_list);
	return (parsed_lex);
}
