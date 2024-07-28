/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varlist_del.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:38:41 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/28 14:38:29 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_varlist(t_varlist *head)
{
	t_varlist	*next;

	if (!head)
		return ;
	while (head)
	{
		next = head->next;
		if (head->key)
		{
			free(head->key);
			head->key = NULL;
		}
		if (head->val)
		{
			free(head->val);
			head->val = NULL;
		}
		free(head);
		head = next;
	}
}

void	del_varlist_node(t_varlist **head, t_varlist **node)
{
	if (!node || !*node || !head || !*head)
		return ;
	if (*head == *node)
		*head = (*node)->next;
	if ((*node)->prev)
		(*node)->prev->next = (*node)->next;
	if ((*node)->next)
		(*node)->next->prev = (*node)->prev;
	free((*node)->key);
	free((*node)->val);
	free(*node);
	*node = NULL;
}

void	del_varlist_key(t_varlist **vlist_head, char *key)
{
	t_varlist	*p;

	if (!*vlist_head || !vlist_head || !key)
		return ;
	p = *vlist_head;
	while (p && ft_strcmp(p->key, key) != 0)
		p = p->next;
	if (!p)
		return ;
	del_varlist_node(vlist_head, &p);
}
