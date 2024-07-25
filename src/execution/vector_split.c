/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:46:31 by marvin            #+#    #+#             */
/*   Updated: 2024/07/25 16:46:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_empty_vector(t_vector *vector)
{
	size_t	index;

	index = 0;
	while (index < vector->size && !vector->buffer[index])
		index++;
	if (index == vector->size)
		return (TRUE);
	return (FALSE);
}

static void	copy_vector_str(char *string, t_vector *vector, size_t vector_index)
{
	size_t	str_index;

	str_index = 0;
	while (vector->buffer[vector_index])
	{
		string[str_index] = vector->buffer[vector_index];
		vector->buffer[vector_index] = '\0';
		vector_index++;
		str_index++;
	}
	string[str_index] = '\0';
}

static char	*split_cmd_strings(t_vector *vector)
{
	size_t	vector_index;
	size_t	word_index;
	size_t	len;
	char	*string;

	if (is_empty_vector(vector))
		return (NULL);
	vector_index = 0;
	len = 0;
	while (vector_index < vector->size && !vector->buffer[vector_index])
		vector_index++;
	word_index = vector_index;
	while (vector->buffer[word_index++])
		len++;
	string = ft_calloc(len + 1, sizeof(char));
	if (!string)
		return (NULL);
	copy_vector_str(string, vector, vector_index);
	return (string);
}

char **make_command_array(t_vector *vector)
{
	size_t	words;
	size_t	array_index;
	char	**cmd_array;	

	words = vector->word_count;
	cmd_array = ft_calloc(words + 1, sizeof(char *));
	if (!cmd_array)
		return (NULL);
	array_index = 0;
	while (array_index < words)
	{
		cmd_array[array_index] = split_cmd_strings(vector);	
		if (!cmd_array[array_index])
		{
			free_strarray(cmd_array);
			return (NULL);
		}
		array_index++;
	}
	cmd_array[array_index] = NULL;
	return (cmd_array);
}
