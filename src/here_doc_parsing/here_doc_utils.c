/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:08:52 by marvin            #+#    #+#             */
/*   Updated: 2024/07/15 22:08:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_heredoc_node(t_heredoc *heredoc, t_data *data)
{
	t_heredoc_data	*roaming;
	t_heredoc_data	*node;
	
	node = ft_calloc(1, sizeof(t_heredoc_data));
	if (!node)
		return ;
	node->heredoc = heredoc;
	node->next = NULL;
	if (!data->heredata)
		data->heredata = node;
	else
	{
		roaming = data->heredata;
		while(roaming->next)	
			roaming = roaming->next;
		roaming->next = node;
	}
}

void	unlink_heredocs(t_data *data)
{
	t_heredoc_data	*roaming;
	t_heredoc_data	*temp;
	t_heredoc_data	*here_data;

	here_data = data->heredata;
	if (!here_data)
		return ;
	roaming = here_data;
	while (roaming)
	{
		temp = roaming;
		if (ft_strlen(temp->heredoc->path))
			if (unlink(temp->heredoc->path) != 0)
				ft_printf("Error deleting file '%s': %s\n",
					temp->heredoc->path, strerror(errno));
		roaming = roaming->next;
		free(temp->heredoc);
		free(temp);
	}
	data->heredata = NULL;
}
