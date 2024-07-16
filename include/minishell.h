/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:21:34 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/16 18:05:36 by jteissie         ###   ########.fr       */
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
# include "lexer.h"
# include "execution.h"
# include "built_ins.h"

typedef struct s_heredoc_data	t_heredoc_data;
typedef struct s_data			t_data;

typedef struct s_heredoc
{
	int		fd;
	char	path[22];
}	t_heredoc;

typedef struct s_heredoc_data
{
	t_heredoc		*heredoc;
	t_heredoc_data	*next;
}	t_heredoc_data;

void		handle_signals(void);
t_heredoc	*process_here_doc(char *limiter);

int			collect_heredocs(t_heredoc_data *here_data, t_data *data);
void		unlink_heredocs(t_heredoc_data *here_data);

char		*get_prompt(char *orig_prompt);

#endif
