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

static void	copy_vector_str(char *string, t_vector *vector, size_t vector_index)
{
	size_t	str_index;

	str_index = 0;
	while (vector->buffer[vector_index])
	{
		string[str_index++] = vector->buffer[vector_index];
		vector->buffer[vector_index] = '\0';
		vector_index++;
	}
	string[str_index] = '\0';
}

static void	trim_vector(t_vector *vector, size_t trim_size)
{
	size_t	new_len;
	char	*trimmed_buffer;
	size_t	trimmed_index;

	new_len = vector->size - trim_size;
	trimmed_index = 0;
	trimmed_buffer = ft_calloc(new_len, sizeof(char));
	if (!trimmed_buffer)
		return ;
	while (trim_size < vector->size)
	{
		trimmed_buffer[trimmed_index] = vector->buffer[trim_size];
		trimmed_index++;
		trim_size++;
	}
	free(vector->buffer);
	vector->size = new_len;
	vector->buffer = trimmed_buffer;
}

static char	*split_cmd_strings(t_vector *vector)
{
	size_t	vector_index;
	size_t	word_index;
	size_t	len;
	char	*string;

	vector_index = 0;
	len = 0;
	if (vector->buffer[vector_index] == '\0')
	{
		string = ft_strdup("");
		trim_vector(vector, 1);
		if (!string)
			return (NULL);
		return (string);
	}
	word_index = vector_index;
	while (vector->buffer[word_index++])
		len++;
	string = ft_calloc(len + 1, sizeof(char));
	if (!string)
		return (NULL);
	copy_vector_str(string, vector, vector_index);
	trim_vector(vector, ft_strlen(string) + 1); //maybe add 1 to ft_strlen call for empty strings??
	return (string);
}

char	**make_command_array(t_vector *vector)
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
