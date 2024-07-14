/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:00:07 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/15 00:33:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	redirect_file(int file_fd[], int mode)
{
	int	dup_status;

	dup_status = 0;
	if (file_fd[0])
	{
		dup_status += dup2(file_fd[0], STDIN_FILENO);
		if (mode == 1)
			close(file_fd[0]);
	}
	if (file_fd[1])
	{
		dup_status += dup2(file_fd[1], STDOUT_FILENO);
		if (mode == 1)
			close(file_fd[1]);
	}
	return (dup_status);
}

int	redirect_child(t_lex_parser *parsed, int p_fd[], int has_pipe[])
{
	if (redirect_pipe(p_fd, has_pipe) < 0)
		return (PANIC);
	if (open_files(parsed) < 0)
		return (PANIC);
	return (SUCCESS);
}
