/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing_errors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:55:49 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/09 15:26:43 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe_errors(t_token *lexer)
{
	t_token	*roaming;
	int		exec_count;

	exec_count = 0;
	roaming = lexer;
	while (roaming)
	{
		if (roaming->type == TK_EXECUTABLE)
			exec_count++;
		roaming = roaming->prev;
	}
	roaming = lexer;
	while (roaming)
	{
		if (roaming->type == TK_EXECUTABLE)
			exec_count++;
		roaming = roaming->next;
	}
	if (exec_count == 2)
		return (FALSE);
	return (TRUE);
}

int	check_redir_errors(t_token *lexer)
{
	t_token	*roaming;

	roaming = lexer;
	while (roaming)
	{
		if (roaming->type == TK_STRING)
			return (FALSE);
		roaming = roaming->next;
	}
	return (TRUE);
}

int	check_parsing_error(t_token *lexer, t_tokentype mode)
{
	if (mode == TK_PIPE)
		return (check_pipe_errors(lexer));
	else if (mode == TK_REDIR)
		return (check_redir_errors(lexer));
	return (FALSE);
}
