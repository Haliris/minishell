/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:25:48 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/16 15:08:18 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_n_flag(char *str)
{
	if (ft_strcmp(str, "-n") == 0)
		return (TRUE);
	return (FALSE);
}

void	sh_echo(char **cmd)
{
	char	*out_str;
	bool	is_flagged;

	if (token->type == TK_PATH)
		out_str = token->path;
	else
		out_str = token->lexstr;
	if (out_str)
		ft_printf("%s", out_str);
	if (!is_flagged)
		ft_printf("\n");
}
