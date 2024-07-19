/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varlist_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:01:52 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/19 17:09:25 by bthomas          ###   ########.fr       */
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
	return (ft_strdup(vlist->val));
}

char	*get_nestedval(t_varlist *vlist, char *key)
{
	char	*val;
	char	*nested_val;
	int		depth;
	char	*curr_key;

	depth = 0;
	curr_key = key;
	val = get_varval(vlist, curr_key);
	if (!val || val[0] != '$')
		return (val);
	while (depth < 5)
	{
		nested_val = get_varval(vlist, val + 1);
		if (!nested_val || nested_val[0] != '$')
		{
			free(val);
			return (nested_val);
		}
		if (depth > 0)
			free(val);
		val = nested_val;
		depth++;
	}
	return (val);
}

bool	in_vlist(t_varlist *vlist, char *key)
{
	while (vlist && ft_strcmp(key, vlist->key) != 0)
		vlist = vlist->next;
	if (vlist)
		return (true);
	return (false);
}
