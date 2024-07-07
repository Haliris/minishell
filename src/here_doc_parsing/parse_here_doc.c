/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_here_doc_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:09:14 by jteissie          #+#    #+#             */
/*   Updated: 2024/06/16 12:29:21 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "get_next_line.h"

//call unlink() in main process once we are done with the file
int	get_random_nbr(int lower, int upper)
{
	int	nbr;
	int	fd;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
		return (-1);
	if (read(fd, &nbr, sizeof(nbr)) < 0)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	nbr = nbr & 0x7FFFFFFF;
	nbr = lower + (nbr % (upper - lower + 1));
	return (nbr);
}

int	randomize(char *str)
{
	char	charset[25];
	int		index;
	int		random;

	index = 0;
	ft_strlcpy(charset, "0123456789abcdefgABCDEFG", 24);
	while (index < 20)
	{
		random = get_random_nbr(0, 23);
		if (random == -1)
			return (-1);
		str[index] = charset[random];
		index++;
	}
	return (1);
}

int	create_here_file(t_heredoc *heredoc)
{
	int		here_fd;

	heredoc->path[0] = '.';
	if (randomize(&heredoc->path[1]) == -1)
		return (-1);
	here_fd = open(heredoc->path, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (here_fd < 0)
		return (-1);
	heredoc->fd = here_fd;
	return (here_fd);
}

int	put_line(char *limiter, int here_fd)
{
	char	*gnl_line;
	int		len;

	len = ft_strlen(limiter);
	while (1)
	{
		gnl_line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(gnl_line, limiter, len) == 0 && gnl_line[len] == '\n')
		{
			free(gnl_line);
			return (1);
		}
		if (!gnl_line)
			return (-1);
		ft_putstr_fd(gnl_line, here_fd);
		free(gnl_line);
	}
}

t_heredoc	*process_here_doc(char *limiter)
{
	int			here_fd;
	t_heredoc	*heredoc;

	heredoc = ft_calloc(1, sizeof(t_heredoc));
	if (!heredoc)
		return (NULL);
	here_fd = create_here_file(heredoc);
	if (here_fd == -1)
		return (NULL);
	if (put_line(limiter, here_fd) < 0)
		return (NULL);
	return (heredoc);
}
