/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:21:33 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/08 19:13:11 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Parse tokens
//If command, recognize it as such
//Else
//Trim '' and ""
//Handle expansion if needed
//We might need lexstr to be **char instead of *char

#include "parser.h"
#include "lexer_dummy.h"
// if first command is cd, then execute it FIRST because the change affects all the children

void	parse_operators(t_lex_parser *parsed, t_token *tokens)
{
	t_token	*roaming;

	roaming = tokens;
	while (roaming != NULL)
	{
		if (roaming->type == TK_PIPE)
			build_pipe_table(parsed, roaming);
		else if (roaming->type == TK_REDIRECTION) // GARBAGE TOKEN TYPES!!!
			build_redirect_table(parsed, roaming);
		else if (roaming->type == TK_REDIRECTION)
			build_redirect_table(parsed, roaming);
		roaming = roaming->next;
	}
}

void	parse_commands(t_lex_parser *parsed, t_token *tokens)
{
	t_token		*roaming;
	t_cmd_table	*table;
	char		*cmd_buffer;

	table = ft_calloc(1, sizeof(t_cmd_table));
	if (!table)
		return ;
	cmd_buffer = NULL;
	roaming = tokens;
	while (roaming)
	{
		if (roaming->type != TK_RESERVED)
		{
			if (cmd_buffer)
				cmd_buffer = re_join_lexstr(cmd_buffer, roaming->lexstr, FORWARD);
			else
				cmd_buffer = roaming->lexstr;
		}
		if (!roaming->next)
			break ;
		roaming = roaming->next;
	}
	if (cmd_buffer)
	{
		table->cmd = cmd_buffer;
		parsed_table_add_back(parsed, table, TK_CMD);
	}
	else
		free(table);
}

t_lex_parser	*interprete_lexer(t_token *tokens_list)
{
	t_lex_parser	*parsed_lex;

	if (check_invalid_token(tokens_list))
		return (NULL);
	parsed_lex = ft_calloc(1, sizeof(t_lex_parser));
	if (!parsed_lex)
		return (NULL); // fuck you nmap
	parsed_lex->next = NULL;
	parse_operators(parsed_lex, tokens_list);
	if (check_remaining_tokens(tokens_list) > 0)
		parse_commands(parsed_lex, tokens_list);
	return (parsed_lex);
}
// GRAMMAR
// " x " prevents from interepreting meta characters EXCEPT $
// 'x' same except for ALL meta characters
// < redirects input
// > redirects output
// << here_doc delimiter from file
// >> redirect output in append mode
// | redirects output of cmd1 and input of cmd2
// $ env variable that needs to be expanded
// $? exist status of the most recently executed foreground pipeline
// ctrl-C ctrl-D and ctrl-\ like bash
// in interactive mode, ctrl-C displays new prompt and interrupts, ctrl-D exits, ctrl-\ does nothing
// builtins are:
//	echo (-n), cd, pwd, export, unset, env, exit
