/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:29:12 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/16 10:22:39 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sh_cd(t_token *token)
{
	char	*path;

	if (token->type == TK_BUILTIN)
		token = token->next;
	if (token->type == TK_PATH)
		path = token->path;
	else
		path = token->lexstr;
	if (chdir(path) != 0)
		ft_printf("minishell: cd: '%s': %s\n", path,
			strerror(errno));
}
