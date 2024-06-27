/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:12:35 by jteissie          #+#    #+#             */
/*   Updated: 2024/06/15 17:21:10 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

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

char	*fetch_line(char *line_stash, int fd, int *status)
{
	char	*read_buff;

	if (!line_stash)
		return (NULL);
	read_buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!read_buff)
		return (free(line_stash), NULL);
	while (!find_eol(line_stash))
	{
		*status = read(fd, read_buff, BUFFER_SIZE);
		if (*status <= 0)
		{
			free(read_buff);
			if (ft_strlen(line_stash) != 0)
				return (line_stash);
			return (free(line_stash), NULL);
		}
		line_stash = ft_str_rejoin(line_stash, read_buff);
		ft_bzero(read_buff, BUFFER_SIZE + 1);
	}
	return (free(read_buff), line_stash);
}

void	get_stash(char *stash, char *line)
{
	int	i;
	int	stash_i;

	i = 0;
	stash_i = 0;
	if (!line)
		return ;
	while (line[i])
	{
		if (line[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	while (line[i])
	{
		stash[stash_i] = line[i];
		line[i] = '\0';
		stash_i++;
		i++;
	}
	stash[stash_i] = '\0';
}

char	*trim_line(char	*untrimmed)
{
	int		i;
	char	*trimmed;

	i = 0;
	if (!untrimmed)
		return (NULL);
	while (untrimmed[i])
		i++;
	trimmed = ft_calloc(i + 1, sizeof(char));
	if (!trimmed)
		return (free(untrimmed), NULL);
	i = 0;
	while (untrimmed[i])
	{
		trimmed[i] = untrimmed[i];
		i++;
	}
	trimmed[i] = '\0';
	return (free(untrimmed), trimmed);
}

char	*get_next_line(int fd)
{
	static char	stash[BUFFER_SIZE + 1];
	char		*line;
	int			status;

	status = 0;
	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_calloc(1, sizeof(char));
	if (ft_strlen(stash))
		line = ft_str_rejoin(line, stash);
	line = fetch_line(line, fd, &status);
	if (status == -1)
	{
		ft_bzero(stash, BUFFER_SIZE + 1);
		return (free(line), NULL);
	}
	get_stash(stash, line);
	line = trim_line(line);
	if (!line)
		return (NULL);
	return (line);
}
/*
#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char *argv[])
{
	int	fd;
	char	*line;
	(void)argc;

	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}*/
