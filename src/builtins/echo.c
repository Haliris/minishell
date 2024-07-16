/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:25:48 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/16 15:03:47 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* needs to print everything until it reaches pipe or redirect */

void	sh_echo(t_data *data, char *cmd)
{
	bool	is_flagged;

	is_flagged = false;
	cmd += 4;
	while (is_space(*cmd))
		cmd++;
	if (ft_strncmp(cmd, "-n ", 3))
	{
		is_flagged = true;
		cmd += 2;
	}
	expand_string_var(data, &cmd);
	ft_printf("%s", cmd);
	if (!is_flagged)
		ft_printf("\n");
}
