/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clean_exit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 19:21:20 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/25 16:11:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_vector(t_vector *vector)
{
	if (!vector)
		return ;
	if (vector->buffer)
	{
		free(vector->buffer);
		vector->buffer = NULL;
	}
	vector->size = 0;
	vector->word_count = 0;
	free(vector);
}

void	free_tables(t_parser *r)
{
	t_cmd_table			*cmd_table;
	t_redirect_table	*redir_table;

	if (!r)
		return ;
	if (r->type == TK_PARS_CMD)
	{
		cmd_table = r->table;
		if (cmd_table)
		{
			free_vector(cmd_table->cmd_buff);
			cmd_table->cmd_buff = NULL;
		}
		free(cmd_table);
		cmd_table = NULL;
	}
	if (r->type == TK_PARS_REDIR)
	{
		redir_table = r->table;
		if (redir_table->redir_str && redir_table->heredoc == FALSE)
			free(redir_table->redir_str);
		free(redir_table);
		redir_table = NULL;
	}
	r->table = NULL;
}

void	free_parsed_mem(t_parser **data)
{
	t_parser	*roaming;
	t_parser	*temp;

	if (!*data)
		return ;
	roaming = *data;
	while (roaming && roaming->prev)
		roaming = roaming->prev;
	while (roaming)
	{
		free_tables(roaming);
		temp = roaming;
		roaming = roaming->next;
		temp->next = NULL;
		temp->prev = NULL;
		free(temp);
	}
	*data = NULL;
}
