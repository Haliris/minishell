/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:25:48 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/16 18:34:30 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_n_flag(char *str)
{
	if (ft_strcmp(str, "-n") == 0)
		return (TRUE);
	return (FALSE);
}

char	*build_echo_str(char **cmd)
{
	char	*out_str;
	int		index;

	index = 0;
	out_str = NULL;
	while (cmd[index])
	{
		if (!out_str)
		{
			out_str = ft_strdup(cmd[index]);
			if (!out_str)
				return (NULL);
		}
		else
		{
			out_str = ft_str_rejoin(out_str, " ");
			if (!out_str)
				return (NULL);
			out_str = ft_str_rejoin(out_str, cmd[index]);
			if (!out_str)
				return (NULL);
		}
		index++;
	}
	return (out_str);
}

void	call_echo(char **cmd)
{
	char	*out_str;
	int		index;
	bool	is_flagged;

	out_str = NULL;
	is_flagged = FALSE;
	index = 1;
	if (!cmd[1])
		ft_printf("\n");
	if (cmd[1])
		is_flagged = check_n_flag(cmd[1]);
	if (is_flagged == TRUE)
		index++;
	out_str = build_echo_str(&cmd[index]);
	if (out_str)
		ft_printf("%s", out_str);
	if (is_flagged == FALSE)
		ft_printf("\n");
	if (out_str)
		free(out_str);
	trash(cmd);
}
