/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varlist_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:01:52 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/16 12:00:38 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_varlist	*get_varlist(char *key, char *val)
{
	t_varlist	*node;

	node = malloc(sizeof(t_varlist));
	if (!node)
		return (NULL);
	node->key = key;
	node->val = val;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

char	*get_varval(t_varlist *vlist, char *key)
{
	while (vlist && ft_strcmp(key, vlist->key) != 0)
		vlist = vlist->next;
	if (!vlist)
		return (NULL);
	return (vlist->val);
}
