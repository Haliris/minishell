/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:57:23 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/11 12:58:35 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
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
