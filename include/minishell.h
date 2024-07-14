/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:21:34 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/14 17:04:01 by bthomas          ###   ########.fr       */
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
# include "hash_table.h"

typedef struct s_heredoc
{
	int		fd;
	char	path[22];
}	t_heredoc;

typedef struct s_data
{
	char			*input;
	char			**env;
	t_token			*token;
	t_hash_table	*env_vars;
	t_hash_table	*local_vars;
}	t_data;

void		handle_signals(void);
t_heredoc	*process_here_doc(char *limiter);
int			clean_exit(t_data *data, int exit_code);

/* Built-ins */
void		sh_echo(t_token *token);
void		sh_cd(t_token *token);

#endif
