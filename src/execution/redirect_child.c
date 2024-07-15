/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:00:07 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/15 13:27:26 by jteissie         ###   ########.fr       */
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

int	redirect_child(t_lex_parser *parsed, int p_fd[], int has_pipe[], int std_fds[])
{
	close(std_fds[0]);
	close(std_fds[1]);
	if (redirect_pipe(p_fd, has_pipe) < 0)
		return (PANIC);
	if (open_files(parsed) < 0)
		return (PANIC);
	return (SUCCESS);
}
