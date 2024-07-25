/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:25:48 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/25 17:15:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_nflag(char *s)
{
	size_t	i;

	i = 1;
	if (s[0] != '-' || !s[1])
		return (false);
	while (s && s[i])
	{
		if (s[i] != 'n')
			return (false);
		i++;
	}
	return (true);
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
	size_t	i;
	bool	is_flagged;

	if (!cmd || !*cmd)
		return ;
	out_str = NULL;
	is_flagged = FALSE;
	i = 1;
	while (cmd[i] && is_nflag(cmd[i]))
	{
		is_flagged = TRUE;
		i++;
	}
	out_str = build_echo_str(&cmd[i]);
	if (out_str && !empty_quote(out_str, 0))
		ft_printf("%s", out_str);
	if (is_flagged == FALSE)
		ft_printf("\n");
	if (out_str)
		free(out_str);
}
