/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:21:34 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/11 13:28:34 by bthomas          ###   ########.fr       */
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

typedef struct s_heredoc
{
	int		fd;
	char	path[22];
}	t_heredoc;

typedef enum e_tokentype
{
	TK_INVALID,
	TK_WORD,
	TK_BUILTIN,
	TK_EXECUTABLE,
	TK_NUMBER,
	TK_PATH,
	TK_HEREDOC,
	TK_PIPE,
	TK_REDIR,
	TK_OPERATOR,
	TK_FLAG,
	TK_STRING,
	TK_EXITSTATUS,
}	t_tokentype;

typedef struct s_token
{
	t_tokentype	type;
	char		*lexstr;
	char		*path;
	t_token		*next;
	t_token		*prev;
}	t_token;

typedef struct s_data
{
	char		*input;
	char		**env;
	t_token		*token;
	size_t		buffer_size;
}	t_data;

void		handle_signals(void);
t_heredoc	*process_here_doc(char *limiter);
int			lexer(t_data *data);

/* Lexing functions */
bool		valid_input(char *input);
bool		invalid_tokens(t_token *token);
void		free_lexmem(t_data *data);

#endif
