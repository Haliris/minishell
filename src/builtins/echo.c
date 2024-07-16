/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:25:48 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/16 10:27:40 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sh_echo(t_data *data, t_token *token)
{
	char	*out_str;
	bool	is_flagged;

	is_flagged = false;
	if (token->type == TK_BUILTIN)
		token = token->next;
	if (token->type == TK_FLAG)
	{
		if (ft_strcmp("-n", token->lexstr) == 0)
			is_flagged = true;
		token = token->next;
	}
	if (token->type == TK_PATH)
		out_str = token->path;
	else
		out_str = token->lexstr;
	expand_string_var(data, out_str);
	if (out_str)
		ft_printf("%s", out_str);
	if (!is_flagged)
		ft_printf("\n");
}
