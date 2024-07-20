/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:57:23 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/20 22:12:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	rl_end_event(void)
{
	return (0);
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
