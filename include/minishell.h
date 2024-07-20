/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:21:34 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/20 11:32:21 by bthomas          ###   ########.fr       */
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
typedef struct s_varlist		t_varlist;

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

typedef struct s_varlist
{
	char		*key;
	char		*val;
	t_varlist	*next;
	t_varlist	*prev;
}	t_varlist;

typedef struct s_data
{
	char			*input;
	char			**env;
	int				errcode;
	char			*prompt;
	t_token			*token;
	t_varlist		*env_vars;
	t_parser		*parsedata;
	t_heredoc_data	*heredata;
}	t_data;

int			init(t_data *data, char **env);

/* Built-ins */
void		export(t_data *data, char *cmd);

/* env vars */
t_varlist	*get_varlist(char *key, char *val);
char		*get_varval(t_varlist *vlist, char *key);
int			add_var(t_varlist **vlist, char *key, char *val);
void		del_varlist(t_varlist *head);
void		del_varlist_node(t_varlist **head, t_varlist *node);
void		del_varlist_key(t_varlist *vlist_head, char *key);
bool		in_vlist(t_varlist *vlist, char *key);
char		*get_nestedval(t_varlist *vlist, char *key);
int			replace_var(t_varlist **vlist, char *key, char *val);

/* cleanup */
void		free_strarray(char **array);
void		free_tokens(t_token *token);
void		free_lexmem(t_data *data);
void		free_env(t_data *data);
int			clean_exit(t_data *data, int exit_code);

/* utils */
void		handle_signals(void);
t_heredoc	*process_here_doc(char *limiter, t_data *data);

void		add_heredoc_node(t_heredoc *heredoc, t_data *data);
void		unlink_heredocs(t_data *data);
int			clean_exit(t_data *data, int exit_code);
char		*get_prompt(char *orig_prompt);
void		expand_string_var(t_data *data, char **str);

bool		var_in_str(char *str);
int			count_str_vars(char *str);

#endif
