/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:00:24 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/20 16:39:39 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line.h"

void	panic(t_parser *parsed)
{
	(void)parsed;
	ft_putstr_fd("free my parsed linked list please\n", STDERR_FILENO);
	ft_putstr_fd("probably exit the process too\n", STDERR_FILENO);
}

char	*build_cmd_buffer(char *cmd_buff, t_token *roaming)
{
	if (cmd_buff)
	{
		cmd_buff = ft_str_rejoin(cmd_buff, " ");
		if (!cmd_buff)
			return (NULL);
		if ((roaming->path && !roaming->prev) || roaming->type == TK_PATH)
			cmd_buff = ft_str_rejoin(cmd_buff, roaming->path);
		else
			cmd_buff = ft_str_rejoin(cmd_buff, roaming->lexstr);
		if (!cmd_buff)
			return (NULL);
	}
	else
	{
		if (roaming->path)
			cmd_buff = ft_strdup(roaming->path);
		else
			cmd_buff = ft_strdup(roaming->lexstr);
	}
	return (cmd_buff);
}

int	parsed_add_back(t_parser *p, void *t, t_parsed_token type)
{
	t_parser	*last;
	t_parser	*new_node;

	if (p->type == TK_PARS_NULL)
	{
		p->table = t;
		p->type = type;
		return (SUCCESS);
	}
	new_node = ft_calloc(1, sizeof(t_parser));
	if (!new_node)
		return (PANIC);
	new_node->table = t;
	new_node->type = type;
	new_node->next = NULL;
	last = p;
	while (last->next)
		last = last->next;
	last->next = new_node;
	new_node->prev = last;
	return (SUCCESS);
}
