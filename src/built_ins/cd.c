/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:29:12 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/16 18:40:44 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	call_cd(char **cmd)
{
	char	*path;

	if (cmd[1] == NULL)
		return ;
	path = cmd[1];
	if (chdir(path) != 0)
		ft_printf("Error: invalid path for cd '%s': %s\n", path, strerror(errno));
	if (cmd)
		trash(cmd);
}
