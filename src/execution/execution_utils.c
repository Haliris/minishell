/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:14:25 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/12 14:18:21 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_redirections(t_lex_parser *table, char *redirection[])
{
	t_lex_parser		*roaming;
	t_redirect_table	*redir;
	char				*outfile;
	char				*infile;

	roaming = NULL;
	infile = NULL;
	outfile = NULL;
	go_to_first_table(roaming, table);
	while (roaming && roaming->type != TK_PARS_PIPE)
	{
		if (roaming->type == TK_PARS_REDIR)
		{
			redir = roaming->table;
			if (redir->type == TK_PARS_IN)
				infile = redir->redir_str;
			else if (redir->type == TK_PARS_OUT)
				outfile = redir->redir_str;
			roaming->type = TK_PARS_RESERVED;
		}
		roaming = roaming->next;
	}
	redirection[0] = infile;
	redirection[1] = outfile;
}

int	open_files(int file_fd[], t_lex_parser *table)
{
	char	*redir[2];

	file_fd[0] = 0;
	file_fd[1] = 0;
	get_redirections(table, redir);
	if (redir[0])
		file_fd[0] = open(redir[0], O_CREAT | O_TRUNC, 064);
	if (redir[1])
		file_fd[1] = open(redir[1], O_CREAT | O_TRUNC, 064);
	if (file_fd[0] < 0 || file_fd[1] < 0)
		return (-1);
	return (SUCCESS);
}

void	go_to_first_table(t_lex_parser *roaming, t_lex_parser *parsed)
{
	roaming = parsed;
	while (roaming->prev && roaming->prev->type != TK_PARS_PIPE)
		roaming = roaming->prev;
}
