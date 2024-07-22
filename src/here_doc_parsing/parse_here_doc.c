/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:09:14 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/21 17:38:30 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#define FILENAME_TAKEN -1
#define SYS_ERROR -2
#define SUCCESS 1

int	get_random_nbr(int lower, int upper)
{
	int	nbr;
	int	fd;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
		return (SYS_ERROR);
	if (read(fd, &nbr, sizeof(nbr)) < 0)
	{
		close(fd);
		return (SYS_ERROR);
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
		random = get_random_nbr(0, 22);
		if (random == SYS_ERROR)
			return (SYS_ERROR);
		str[index] = charset[random];
		index++;
	}
	if (access(str, F_OK) == 0)
		return (FILENAME_TAKEN);
	return (SUCCESS);
}

int	create_here_file(t_heredoc *heredoc)
{
	int		here_fd;
	int		randomize_status;

	heredoc->path[0] = '.';
	randomize_status = FILENAME_TAKEN;
	while (randomize_status == FILENAME_TAKEN)
	{
		randomize_status = randomize(&heredoc->path[1]);
		if (randomize_status == SYS_ERROR)
			return (SYS_ERROR);
	}
	here_fd = open(heredoc->path, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (here_fd < 0)
		return (SYS_ERROR);
	heredoc->fd = here_fd;
	return (here_fd);
}

int	put_line(char *limiter, int here_fd)
{
	char	*line;
	int		len;

	len = ft_strlen(limiter);
	signal(SIGINT, interrupt_heredoc);
	while (1)
	{
		line = readline("> ");
		if (g_sig_offset)
		{
			if (line)
				free(line);
			return (SUCCESS);
		}
		if (!line)
			return (SUCCESS);
		if (ft_strncmp(line, limiter, len) == 0)
		{
			free(line);
			return (SUCCESS);
		}
		ft_putendl_fd(line, here_fd);
		free(line);
	}
}

t_heredoc	*process_here_doc(char *limiter, t_data *data)
{
	int			here_fd;
	t_heredoc	*heredoc;

	heredoc = ft_calloc(1, sizeof(t_heredoc));
	if (!heredoc)
		return (NULL);
	heredoc->path[0] = 0;
	here_fd = create_here_file(heredoc);
	if (here_fd == SYS_ERROR)
	{
		free(heredoc);
		return (NULL);
	}
	if (put_line(limiter, here_fd) < 0 || g_sig_offset)
	{
		close(here_fd);
		unlink(heredoc->path);
		free(heredoc);
		return (NULL);
	}
	close(here_fd);
	add_heredoc_node(heredoc, data);
	return (heredoc);
}

#undef FILENAME_TAKEN
#undef SYS_ERROR
#undef SUCCESS
