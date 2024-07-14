/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:00:07 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/14 13:50:16 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_pipe(int p_fd[], int has_pipe[])
{
	int	dup_status;

	dup_status = 0;
	close(p_fd[0]);
	if (has_pipe[1] == TRUE)
		dup_status += dup2(p_fd[1], STDOUT_FILENO);
	close(p_fd[1]);
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

int	redirect_child(int file_fd[], int p_fd[], int has_pipe[])
{
	if (redirect_pipe(p_fd, has_pipe) < 0)
		return (PANIC);
	if (redirect_file(file_fd, 1) < 0)
		return (PANIC);
	return (SUCCESS);
}
