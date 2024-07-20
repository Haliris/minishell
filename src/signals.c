/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:57:23 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/20 12:53:17 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	sigint(int sig)
{
	(void)sig;
	global_sig.sigcode = sig;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	global_sig.sigcode = 0;
}

/* ctrl \ */
void	sigquit(int sig)
{
	(void)sig;
}

void	handle_signals(void)
{
	signal(SIGINT, sigint);
	signal(SIGQUIT, sigquit);
}
