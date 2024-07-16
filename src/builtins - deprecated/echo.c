/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:25:48 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/16 14:26:44 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* needs to print everything until it reaches pipe or redirect */

void	sh_echo(t_data *data, char *cmd)
{
	char	*out_str;
	bool	is_flagged;

	is_flagged = false;
	cmd += 4;
	while (is_space(*cmd))
		cmd++;
	if (ft_strncmp(cmd, "-n ", 3))
	{
		is_flagged = true;
		cmd + 2;
	}
	expand_string_var(data, cmd);
	if (!is_flagged)
		ft_printf("\n");
}
