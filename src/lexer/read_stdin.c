/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_stdin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bento <bento@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:29:27 by bthomas           #+#    #+#             */
/*   Updated: 2024/06/28 17:47:51 by bento            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	increase_buffer(t_data *data)
{
	char	*new_buff;
	size_t	new_size;

	new_size = data->buffer_size + INIT_BUFF_SIZE;
	new_buff = (char *)malloc(new_size);
	if (!new_buff)
		return (1);
	ft_memmove(new_buff, data->input, data->buffer_size);
	free(data->input);
	data->input = new_buff;
	return (0);
}

int	read_stdin(char **argv, t_data *data)
{
	char	c;
	size_t	bytes_read;

	data->input = (char *)malloc(data->buffer_size);
	if (!data->input)
		return (1);
	ft_bzero(data->input, data->buffer_size);
	bytes_read = 0;
	while (read(0, &c, 1) > 0 && c!= '\n' && c != EOF)
	{
		data->input[bytes_read] = c;
		bytes_read++;
		if (bytes_read == MAX_INPUT_LEN - 1)
			return (1);
		if (bytes_read == data->buffer_size - 1)
			if (increase_buffer(data))
				return (1);
	}
	data->input[bytes_read] = '\0';
	return (0);
}
/* cc -I./include -I./libft src/read_stdin.c libft/ft_memmove.c libft/ft_bzero.c */
int		main(int argc, char **argv)
{
	t_data	data;

	data.input = NULL;
	data.buffer_size = INIT_BUFF_SIZE;
	if (read_stdin(argv, &data))
	{
		if (data.input)
			free(data.input);
		return (1);
	}
	return (0);
}
