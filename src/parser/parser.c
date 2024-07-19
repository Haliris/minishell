/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:21:33 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/18 17:09:29 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*assemble_cmd(t_token *roaming)
{
	char	*cmd_buff;

	cmd_buff = NULL;
	while (roaming && roaming->type != TK_PIPE)
	{
		if (roaming->type != TK_RESERVED)
		{
			cmd_buff = build_cmd_buffer(cmd_buff, roaming);
			roaming->type = TK_RESERVED;
		}
		roaming = roaming->next;
	}
	return (cmd_buff);
}

void	parse_command(t_parser *parsed, t_token *roaming)
{
	t_cmd_table	*table;

	table = ft_calloc(1, sizeof(t_cmd_table));
	if (!table)
		return ;
	while (roaming->prev && roaming->prev->type != TK_PIPE)
		roaming = roaming->prev;
	table->cmd = assemble_cmd(roaming);
	if (table->cmd)
		parsed_add_back(parsed, table, TK_PARS_CMD);
	else
		free(table);
}

void	collect_redir_tk(t_parser *parsed, t_token *roaming)
{
	while (roaming && roaming->type != TK_PIPE)
	{
		if (roaming->type == TK_REDIR || roaming->type == TK_HEREDOC)
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

void	parse_operators(t_parser *parsed, t_token *tokens)
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

int	interprete_lexer(t_data *data)
{
	t_parser		*parsed;
	t_token			*tokens_list;

	parsed = data->parsedata;
	tokens_list = data->token;
	parse_operators(parsed, tokens_list);
	data->parsedata = parsed;
	return (SUCCESS);
}
