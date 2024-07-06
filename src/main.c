/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:43:42 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/05 15:52:28 by jteissie         ###   ########.fr       */
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
	t_pipe_table	*pipe;

	int	i = 0;

	lexer = malloc(sizeof(t_token));
	temp_lexer = NULL;
	lexer->lexstr = "cat";
	lexer->type = TK_EXECUTABLE;
	lexer->prev = NULL;
	lexer->next = temp_lexer;
	while (i < 4)
	{
		last = lexer;
		temp_lexer = malloc(sizeof(t_token));
		while(last->next)
			last = last->next;
		switch (i)
		{
			case 0:
			{
				temp_lexer->lexstr = "-e";
				temp_lexer->type = TK_STRING;
				break ;
			}	
			case 1:
			{
				temp_lexer->lexstr = "|";
				temp_lexer->type = TK_PIPE;
				break ;
			}
			case 2:
			{
				temp_lexer->lexstr = "grep";
				temp_lexer->type = TK_EXECUTABLE;
				break ;
			}
			case 3:
			{
				temp_lexer->lexstr = "cc";
				temp_lexer->type = TK_STRING;
				break ;
			}
			case 4:
			{
				temp_lexer->lexstr = "ls";
				temp_lexer->type = TK_EXECUTABLE;
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
	while (roaming)
	{
		printf("%p\n", roaming->table);
		pipe = roaming->table;
		printf("%s\n", pipe->cmd1);
		printf("%s\n", pipe->cmd2);
		roaming = roaming->next;
	}
	(void)ac;
	(void)av;
	return (0);
}
