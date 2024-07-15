/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:00:07 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/15 19:32:56 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_files(int file_fd[], int *heredoc_fd)
{
	int	dup_status;

	dup_status = 0;
	if (*heredoc_fd > 0)
	{
		dup_status += dup2(*heredoc_fd, STDIN_FILENO);
		close(*heredoc_fd);
		*heredoc_fd = 0;
	}
	else if (file_fd[0])
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

int	open_files(char *redir[], int file_fd[])
{
	if (redir[0])
		file_fd[0] = open(redir[0], O_RDONLY);
	if (redir[1])
		file_fd[1] = open(redir[1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (file_fd[0] < 0 || file_fd[1] < 0)
		return (PANIC);
	return (SUCCESS);
}

int	process_files(t_lex_parser *table)
{
	char			*redir[2];
	int				heredoc_fd;
	int				file_fd[2];
	t_lex_parser	*roaming;

	file_fd[0] = 0;
	file_fd[1] = 0;
	redir[0] = NULL;
	redir[1] = NULL;
	roaming = table;
	while (roaming->prev && roaming->prev->type != TK_PARS_PIPE)
		roaming = roaming->prev;
	while (roaming && roaming->type != TK_PARS_PIPE)
	{
		heredoc_fd = 0;
		if (roaming->type == TK_PARS_REDIR)
		{
			if (get_redirections(roaming, redir, &heredoc_fd) < 0)
				return (-1);
			if (open_files(redir, file_fd) == PANIC)
				return (-1);
			if (redirect_files(file_fd, &heredoc_fd) < 0)
				return (-1);
		}
		roaming = roaming->next;
		redir[0] = NULL;
		redir[1] = NULL;
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
