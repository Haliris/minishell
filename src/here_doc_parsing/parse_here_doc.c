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
#include <time.h>
#include <stdlib.h>
#include "get_next_line.h"

// call unlink on the returned fd to remove said file once it is parsed in the main process
int	get_random_nbr(int lower, int upper);
{
	int	nbr;

	nbr = ((rand() % (upper - lower + 1)) + lower);
	return (nbr);
}

void	randomize(char *str)
{
	char	charset[24];
	int		index;
	int		random;

	charset = "0123456789abcdefgABCDEFG";
	index = 0;
	while (index < 20)
	{
		random = get_random_nbr(0, 23); 
		str[index] = charset[random];
		index++;
	}
}

int	create_here_file(void)
{
	char	random_str[20];
	int		here_fd;

	randomize(random_str);
	here_fd = open(random_str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	return (here_fd);
}

void	put_line(char *limiter)
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
			exit(EXIT_SUCCESS);
		}
		if (!gnl_line)
			handle_error("Couldn't find LIMITER in here_doc", EXIT_FAILURE);
		ft_putstr_fd(gnl_line, STDOUT_FILENO);
		free(gnl_line);
	}
}

int	process_here_doc(char *limiter)
{
	int		here_fd;

	here_fd = create_here_file();
	put_line(limiter);
	return (here_fd);
}

int main(int ac, char *av[])
{
	void(ac);
	process_here_doc(av[1]);
	return (0);
}