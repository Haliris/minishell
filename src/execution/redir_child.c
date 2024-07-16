/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:00:07 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/16 11:53:52 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_files(int file_fd[])
{
	int	dup_status;

	dup_status = 0;
	if (file_fd[0])
	{
		dup_status += dup2(file_fd[0], STDIN_FILENO);
		close(file_fd[0]);
		file_fd[0] = 0;
	}
	if (file_fd[1])
	{
		dup_status += dup2(file_fd[1], STDOUT_FILENO);
		close(file_fd[1]);
		file_fd[1] = 0;
	}
	return (dup_status);
}

int	open_files(char *redir[], int file_fd[], int *append)
{
	if (redir[0])
		file_fd[0] = open(redir[0], O_RDONLY);
	if (redir[1])
	{
		if (*append == TRUE)
			file_fd[1] = open(redir[1], O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (*append == FALSE)
			file_fd[1] = open(redir[1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	}
	*append = FALSE;
	if (file_fd[0] < 0 || file_fd[1] < 0)
		return (PANIC);
	redir[0] = NULL;
	redir[1] = NULL;
	return (SUCCESS);
}

int	process_files(t_lex_parser *table)
{
	char			*redir[2];
	int				f_fd[2];
	int				append;
	t_lex_parser	*roaming;

	f_fd[0] = 0;
	f_fd[1] = 0;
	redir[0] = NULL;
	redir[1] = NULL;
	roaming = table;
	while (roaming->prev && roaming->prev->type != TK_PARS_PIPE)
		roaming = roaming->prev;
	while (roaming && roaming->type != TK_PARS_PIPE)
	{
		if (roaming->type == TK_PARS_REDIR)
		{
			append = get_redirections(roaming, redir);
			if (open_files(redir, f_fd, &append) == PANIC
				|| redir_files(f_fd) < 0)
				return (-1);
		}
		roaming = roaming->next;
	}
	return (SUCCESS);
}

int	redirect_pipe(int p_fd[], int has_pipe[])
{
	int	dup_status;

	dup_status = 0;
	close(p_fd[0]);
	p_fd[0] = -1;
	if (has_pipe[1] == TRUE)
		dup_status += dup2(p_fd[1], STDOUT_FILENO);
	close(p_fd[1]);
	p_fd[1] = -1;
	return (dup_status);
}

int	redir_child(t_lex_parser *p, int p_fd[], int has_pipe[], int std_fds[])
{
	close(std_fds[0]);
	close(std_fds[1]);
	if (redirect_pipe(p_fd, has_pipe) < 0)
		return (PANIC);
	if (process_files(p) < 0)
		return (PANIC);
	return (SUCCESS);
}