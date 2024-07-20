/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:57:23 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/20 17:30:35 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	rl_end_event(void)
{
	return (0);
}

void	interrupt_heredoc(int status)
{
	(void)status;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	rl_done = 1;
	global_sig.heredoc_int = TRUE;
	global_sig.sigcode = 0;
}

void	interrupt_exec(int status)
{
	(void)status;
	write(STDERR_FILENO, "\n", 1);
}

void	interrupt_main(int status)
{
	(void)status;
	global_sig.sigcode = status;
	write(STDIN_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	global_sig.sigcode = 0;
}
void	setup_signals(void)
{
	signal(SIGINT, interrupt_main);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	init_signals(void)
{
	rl_event_hook = rl_end_event;
	setup_signals();
}

