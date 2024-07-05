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
	t_token		*lexer2;
	t_token		*lexer3;
	t_token		*lexer4;
	t_lex_parser	*parser;
	t_lex_parser	*roaming;

	lexer = ft_calloc(1, sizeof(t_token));
	lexer2 = ft_calloc(1, sizeof(t_token));
	lexer3 = ft_calloc(1, sizeof(t_token));
	lexer4 = ft_calloc(1, sizeof(t_token));
	parser = ft_calloc(1, sizeof(t_lex_parser));
	roaming = ft_calloc(1, sizeof(t_lex_parser));

	lexer->lexstr = "cat";
	lexer->type = TK_EXECUTABLE;
	lexer2->lexstr = "|";
	lexer2->type = TK_PIPE;
	lexer3->lexstr = "grep";
	lexer3->type = TK_EXECUTABLE;
	lexer4->lexstr = "cc";
	lexer4->type = TK_STRING;

	lexer->prev = NULL;
	lexer->next = lexer2;
	lexer2->prev = lexer;
	lexer2->next = lexer3;
	lexer3->prev = lexer2;
	lexer3->next = lexer4;
	lexer4->prev = lexer3;
	lexer4->next = NULL;

	parser = interprete_lexer(lexer);
	roaming = parser;
	while (roaming)
	{
		printf("%p\n", roaming->table);
		roaming = roaming->next;
	}
	// free(lexer);
	// free(lexer2);
	// free(lexer3);
	// free(lexer4);
	// free(parser);
	// free(roaming);
	(void)ac;
	(void)av;
	return (0);
}
