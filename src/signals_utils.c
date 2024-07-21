/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 22:05:54 by marvin            #+#    #+#             */
/*   Updated: 2024/07/20 22:05:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	interrupt_heredoc(int status)
{
	(void)status;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	rl_done = 1;
	g_sig.heredoc_int = TRUE;
}

void	interrupt_exec(int status)
{
	(void)status;
	write(STDERR_FILENO, "\n", 1);
}

void	interrupt_main(int status)
{
	(void)status;
	write(STDIN_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
