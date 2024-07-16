/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:21:34 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/16 11:05:43 by bthomas          ###   ########.fr       */
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

typedef struct s_heredoc
{
	int		fd;
	char	path[22];
}	t_heredoc;

typedef struct s_varlist
{
	char		*key;
	char		*val;
	t_varlist	*next;
	t_varlist	*prev;
}	t_varlist;

typedef struct s_data
{
	char		*input;
	char		**env;
	t_token		*token;
	t_varlist	*env_vars;
}	t_data;

void		handle_signals(void);
t_heredoc	*process_here_doc(char *limiter);
int			clean_exit(t_data *data, int exit_code);
void		expand_string_var(t_data *data, char **str);

/* Built-ins */
void		sh_echo(t_data *data, t_token *token);
void		sh_cd(t_token *token);
void		export(t_data *data, t_token *token);

/* env vars */
t_varlist	*get_varlist(char *key, char *val);
char		*get_varval(t_varlist *vlist, char *key);
int			add_var(t_varlist **vlist, char *key, char *val);
void		del_varlist(t_varlist *head);
void		del_varlist_node(t_varlist **head, t_varlist *node);
void		del_varlist_key(t_varlist *vlist_head, char *key);

#endif
