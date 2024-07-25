/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:00:24 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/25 17:14:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_strings_vector(char *str, char *add, t_vector *vector)
{
	char		*new_str;
	size_t		len;
	size_t		str_index;
	size_t		new_index;

	str_index = 0;
	new_index = 0;
	len = vector->size + ft_strlen(add);
	new_str = ft_calloc(len + 2, sizeof(char));
	if (!new_str)
		return (free(str), NULL);
	while (str_index < vector->size)
		new_str[new_index++] = str[str_index++];
	new_str[new_index++] = '\0';
	free(str);
	str_index = 0;
	while (add[str_index])
		new_str[new_index++] = add[str_index++];
	new_str[new_index] = '\0';
	return (new_str);
}

char	*vector_add_back(char *str, char *add, t_vector *vector)
{
	str = join_strings_vector(str, add, vector);
	if (!str)
		return (NULL);
	vector->size += ft_strlen(add) + 2;
	vector->word_count += 1;
	return (str);
}

char	*vector_dup(char *str, t_vector *vector)
{
	char	*dup_str;

	dup_str = NULL;
	dup_str = ft_strdup(str);
	if (!dup_str)
		return (NULL);
	vector->word_count += 1;
	vector->size += ft_strlen(str) + 1;
	return (dup_str);
}

char	*build_cmd_buff(t_vector *t, char *cmd_buff, t_token *roaming)
{
	if (cmd_buff)
	{
		if ((roaming->path && !roaming->prev) || roaming->type == TK_PATH)
			cmd_buff = vector_add_back(cmd_buff, roaming->path, t);
		else
			cmd_buff = vector_add_back(cmd_buff, roaming->lexstr, t);
		if (!cmd_buff)
			return (NULL);
	}
	else
	{
		if (roaming->path)
			cmd_buff = vector_dup(roaming->path, t);
		else
			cmd_buff = vector_dup(roaming->lexstr, t);
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
