/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:21:33 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/12 19:02:13 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line.h"

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
			{
				cmd_buff = ft_str_rejoin(cmd_buff, " ");
				cmd_buff = ft_str_rejoin(cmd_buff, roaming->lexstr);
				if (!cmd_buff)
					return (NULL);
			}
			else
				cmd_buff = ft_strdup(roaming->lexstr);
			roaming->type = TK_RESERVED;
		}
		roaming = roaming->next;
	}
	return (cmd_buff);
}

void	parse_command(t_lex_parser *parsed, t_token *roaming)
{
	t_cmd_table	*table;

	table = ft_calloc(1, sizeof(t_cmd_table));
	if (!table)
		return ;
	while (roaming->prev && roaming->prev->type != TK_PIPE)
		roaming = roaming->prev;
	table->cmd = make_cmd_buffer(roaming);
	if (table->cmd)
		parsed_add_back(parsed, table, TK_PARS_CMD);
	else
		free(table);
}

void	collect_redir_tk(t_lex_parser *parsed, t_token *roaming)
{
	while (roaming && roaming->type != TK_PIPE)
		{
			if (roaming->type == TK_REDIR)
			{
				if (build_redirect_table(parsed, roaming) == PANIC)
					panic(parsed);
				roaming->type = TK_RESERVED;
			}
			roaming = roaming->next;
		}
	if (roaming && roaming->prev && roaming->type == TK_PIPE)
		roaming = roaming->prev;
}

void	parse_operators(t_lex_parser *parsed, t_token *tokens)
{
	t_token	*roaming;

	roaming = tokens;
	while (roaming)
	{
		collect_redir_tk(parsed, roaming);
		parse_command(parsed, roaming);
		while (roaming && roaming->type != TK_PIPE)
		{
			roaming = roaming->next;
			if (roaming && roaming->type == TK_PIPE)
			{
				parsed_add_back(parsed, NULL, TK_PARS_PIPE);
				if (roaming->next)
					roaming = roaming->next;
				break ;
			}
		}
	}
}

int	interprete_lexer(t_lex_parser *parsed, t_token *tokens_list)
{

	if (check_invalid_token(tokens_list))
		return (PANIC);
	parsed->next = NULL;
	parsed->prev = NULL;
	parsed->type = 0;
	parsed->table = NULL;
	parse_operators(parsed, tokens_list);
	if (!parsed->table)
		return (PANIC);
	return (SUCCESS);
}
