/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varlist_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:38:28 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/15 15:16:08 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_var(t_varlist **vlist, char *key, char *val)
{
	t_varlist	*node;
	t_varlist	*curr;

	node = get_varlist(key, val);
	if (!node)
		return (1);
	if (!*vlist)
	{
		*vlist = node;
		return (0);
	}
	curr = *vlist;
	while (curr->next)
		curr = curr->next;
	curr->next = node;
	node->prev = curr;
	return (0);
}
