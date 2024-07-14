/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:25:48 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/13 13:48:35 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sh_echo(t_token *token)
{
	char	*out_str;
	bool	is_flagged;

	is_flagged = false;
	if (token->type == TK_BUILTIN)
		token = token->next;
	if (token->type == TK_FLAG)
	{
		if (ft_strncmp("-n", token->lexstr, 2) == 0
			&& ft_strlen(token->lexstr) == 2)
			is_flagged = true;
		token = token->next;
	}
	if (token->type == TK_PATH)
		out_str = token->path;
	else
		out_str = token->lexstr;
	if (out_str)
		ft_printf("%s", out_str);
	if (!is_flagged)
		ft_printf("\n");
}
