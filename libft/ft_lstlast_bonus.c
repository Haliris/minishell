/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:36:42 by jteissie          #+#    #+#             */
/*   Updated: 2024/05/18 18:59:01 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*temp;
	t_list	*last;

	if (lst == NULL)
		return (NULL);
	temp = lst;
	while (temp != NULL)
	{
		last = temp;
		temp = temp->next;
	}
	return (last);
}
