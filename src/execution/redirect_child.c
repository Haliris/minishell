/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:00:07 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/12 15:35:03 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_pipe(int p_fd[], int index)
{
	int	dup_status;

	dup_status = 0;
	close(p_fd[0]);
	if (index > 0)
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

int	redirect_child(int file_fd[], int p_fd[], int index)
{
	if (redirect_pipe(p_fd, index) < 0)
		return (PANIC);
	if (redirect_file(file_fd, 1) < 0)
		return (PANIC);
	return (SUCCESS);
}
