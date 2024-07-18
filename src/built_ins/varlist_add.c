/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varlist_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:38:28 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/18 17:28:54 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	replace_var(t_varlist **vlist, char *key, char *val)
{
	t_varlist	*curr;

	curr = *vlist;
	while (curr && ft_strcmp(key, curr->key) != 0)
		curr = curr->next;
	if (curr && curr->val)
	{
		if (curr->val)
			free(curr->val);
		curr->val = val;
	}
	return (0);
}

int	add_var(t_varlist **vlist, char *key, char *val)
{
	t_varlist	*node;
	t_varlist	*curr;

	if (in_vlist(*vlist, key))
		return (replace_var(vlist, key, val));
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
