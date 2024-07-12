/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:00:07 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/12 14:33:58 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_pipe(int p_fd[], int file_fd[])
{
	int	dup_status;

	dup_status = 0;
	if (!file_fd[0] && p_fd[0] == TRUE)
		dup_status += dup2(p_fd[0], STDIN_FILENO);
	if (!file_fd[1] && p_fd[1] == TRUE)
		dup_status += dup2(p_fd[1], STDIN_FILENO);
	if (file_fd[0] < 0 || file_fd[1] < 0)
	{
		if (file_fd[0])
			close(file_fd[0]);
		if (file_fd[1])
			close (file_fd[1]);
		return (-1);
	}
	return (dup_status);
}

int	redirect_file(int file_fd[])
{
	int	dup_status;

	dup_status = 0;
	if (file_fd[0])
	{
		dup_status += dup2(file_fd[0], STDIN_FILENO);
		close(file_fd[0]);
	}
	if (file_fd[1])
	{
		dup_status += dup2(file_fd[1], STDOUT_FILENO);
		close(file_fd[1]);
	}
	return (dup_status);
}

void	redirect_child(int file_fd[], int p_fd[])
{
	if (redirect_pipe(p_fd, file_fd) < 0)
		return ;
	if (redirect_file(file_fd) < 0)
		return ;
	close(p_fd[0]);
	close(p_fd[1]);
}
