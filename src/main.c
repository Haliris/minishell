/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:43:42 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/08 18:53:01 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>

int	main(int ac, char **av)
{
	t_token		*lexer;
	t_token		*temp_lexer;
	t_token		*last;
	t_lex_parser	*parser;
	t_lex_parser	*roaming;

	int	i = 0;

	lexer = malloc(sizeof(t_token));
	temp_lexer = NULL;
	lexer->lexstr = "cat";
	lexer->type = TK_EXECUTABLE;
	lexer->prev = NULL;
	lexer->next = temp_lexer;
	while (i < 6)
	{
		last = lexer;
		temp_lexer = malloc(sizeof(t_token));
		while(last->next)
			last = last->next;
		switch (i)
		{
			case 0:
			{
				temp_lexer->lexstr = "<";
				temp_lexer->type = TK_REDIRECTION;
				break ;
			}
			case 1:
			{
				temp_lexer->lexstr = "Makefile";
				temp_lexer->type = TK_STRING;
				break ;
			}
			case 2:
			{
				temp_lexer->lexstr = "grep";
				temp_lexer->type = TK_STRING;
				break ;
			}
			case 3:
			{
				temp_lexer->lexstr = ">";
				temp_lexer->type = TK_REDIRECTION;
				break ;
			}
			case 4:
			{
				temp_lexer->lexstr = "outfile";
				temp_lexer->type = TK_STRING;
				break ;
			}
			case 5:
			{
				temp_lexer->lexstr = "cc";
				temp_lexer->type = TK_STRING;
				break ;
			}
		}
		last->next = temp_lexer;
		temp_lexer->next = NULL;
		temp_lexer->prev = last;
		i++;
	}
	parser = interprete_lexer(lexer);
	roaming = parser;

	t_pipe_table		*pipe;
	t_redirect_table	*redir;
	t_cmd_table			*cmd;
	while (roaming)
	{
		if (roaming->type == TK_INFILE)
		{
			redir = roaming->table;
			printf("redir:%s\n", redir->redir_str);
		}
		if (roaming->type == TK_PIPE)
		{
			pipe = roaming->table;
			printf("cmd1:%s\n", pipe->cmd1);
			printf("cmd2:%s\n", pipe->cmd2);
		}
		else if (roaming->type == TK_CMD)
		{
			cmd = roaming->table;
			printf("lone command:%s\n", cmd->cmd);
		}
		roaming = roaming->next;
	}
	(void)ac;
	(void)av;
	return (0);
}
