/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:21:34 by bthomas           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/07/09 18:55:26 by jteissie         ###   ########.fr       */
=======
/*   Updated: 2024/07/11 14:52:40 by bthomas          ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"
# include "get_next_line.h"
# include "parser.h"
<<<<<<< HEAD
# include "execution.h"
=======
# include "lexer.h"
>>>>>>> main

typedef struct s_heredoc
{
	int		fd;
	char	path[22];
}	t_heredoc;

void	handle_signals(void);

#endif
