/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:00:24 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/25 11:46:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	panic(t_parser *parsed)
{
	(void)parsed;
	ft_putstr_fd("free my parsed linked list please\n", STDERR_FILENO);
	ft_putstr_fd("probably exit the process too\n", STDERR_FILENO);
}

char	*join_strings_vector(char *str, char *add)
{
	char	*new_str;
	size_t	len;
	int		str_index;
	int		new_index;

	str_index = 0;
	new_index = 0;
	len = ft_strlen(str + 1) + ft_strlen(add);
	new_str = ft_calloc(len + 1, sizeof(char));
	if (!new_str)
		return (free(str), NULL);
	while (str[str_index])	
		new_str[new_index++] = str[str_index++];	
	new_str[new_index++] = '\0'
	free(str);
	new_index++;
	str_index = 0;
	while (add[str_index])
		new_str[new_index++] = add[str_index++];	
	new_str[new_index] = '\0'
	return (new_str);
}

void	vector_add_back(char *str, char *add, t_vector *vector)
{
	str = join_strings_vector(str, add)
	if (!str)
		return (NULL);
	vector->size += ft_strlen(add);
	vector->word_count += 1;
}

void	vector_dup(char *str, t_vector *vector)
{
	vector->buffer = ft_strdup(str);
	if (!vector->buffer)
		return ;
	vector->word_count += 1;
	vector->size += ft_strlen(str);
}

char	*build_cmd_buffer(t_vector *table, char *cmd_buff, t_token *roaming)
{
	if (cmd_buff)
	{
		cmd_buff = ft_str_rejoin(cmd_buff, " ");
		if (!cmd_buff)
			return (NULL);
		if ((roaming->path && !roaming->prev) || roaming->type == TK_PATH)
			cmd_buff = vector_add_back(cmd_buff, roaming->path, table);
		else
			cmd_buff = vector_add_back(cmd_buff, roaming->lexstr, table);
		if (!cmd_buff)
			return (NULL);
	}
	else
	{
		if (roaming->path)
			cmd_buff = vector_dup(roaming->path, table);
		else
			cmd_buff = vector_dup(roaming->lexstr, table);
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
