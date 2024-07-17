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

int	heredoc_add_back(t_heredoc_data *data, t_token *roaming)
{
	t_heredoc_data	*temp;
	t_heredoc_data	*new_node;

	temp = data;
	while (temp->next)
		temp = temp->next;
	new_node = ft_calloc(1, sizeof(t_heredoc_data));
	if (!new_node)
		return (PANIC);
	new_node->heredoc = roaming->heredoc;
	new_node->next = NULL;
	temp->next = new_node;
	return (SUCCESS);
}

int	collect_heredocs(t_data *data)
{
	t_heredoc_data	*here_data;
	t_token			*roaming;

	here_data = data->heredata;
	roaming = data->token;
	while (roaming)
	{
		if (roaming->type == TK_HEREDOC)
		{
			if (!here_data->heredoc)
				here_data->heredoc = roaming->heredoc;
			else
			{
				if (heredoc_add_back(here_data, roaming) == PANIC)
					return (PANIC);
			}
		}
		roaming = roaming->next;
	}
	return (SUCCESS);
}

void	unlink_heredocs(t_data *data)
{
	t_heredoc_data	*roaming;
	t_heredoc_data	*temp;
	int				index;
	t_heredoc_data	*here_data;

	here_data = data->heredata;
	if (!here_data->heredoc)
		return ;
	roaming = here_data;
	index = 0;
	while (roaming)
	{
		temp = roaming;
		if (ft_strlen(temp->heredoc->path))
			if (unlink(temp->heredoc->path) != 0)
				ft_printf("Error deleting file '%s': %s\n",
					temp->heredoc->path, strerror(errno));
		free(temp->heredoc);
		if (index > 0)
			free(temp);
		roaming = roaming->next;
	}
	here_data->heredoc = NULL;
}
