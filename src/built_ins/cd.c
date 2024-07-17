/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:29:12 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/17 13:41:30 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	call_cd(char **cmd)
{
	char	*p;

	if (cmd[1] == NULL)
		return ;
	p = cmd[1];
	if (chdir(p) != 0)
		ft_printf("Error: invalid path for cd '%s': %s\n", p, strerror(errno));
	if (cmd)
		trash(cmd);
}
