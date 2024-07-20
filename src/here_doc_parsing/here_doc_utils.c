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

char	*ft_str_rejoin(char *stash, char *add)
{
	char	*joined;

	if (!stash)
		return (NULL);
	joined = ft_calloc((ft_strlen(stash) + ft_strlen(add) + 1), sizeof(char));
	if (!joined)
		return (free(stash), NULL);
	copy_and_cat(joined, stash, add);
	return (free(stash), joined);
}

void	copy_and_cat(char *out, char *cpy_src, char *cat_src)
{
	int	i;
	int	src_i;

	i = 0;
	src_i = 0;
	while (cpy_src[src_i])
	{
		out[i] = cpy_src[src_i];
		i++;
		src_i++;
	}
	src_i = 0;
	while (cat_src[src_i])
		out[i++] = cat_src[src_i++];
	out[i] = '\0';
}

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
		while (roaming->next)
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
