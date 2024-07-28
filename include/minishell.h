/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:47:59 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/27 16:34:29 by bthomas          ###   ########.fr       */
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
# include "parser.h"
# include "lexer.h"
# include "execution.h"
# include "built_ins.h"
# define SIG_OFFSET 128
# define NOT_FOUND 127
# define HEREDOC_INTERRUPT 2
# define LEXER_ERROR 1
# define CANNOT_EXECUTE 126

typedef struct s_heredoc_data	t_heredoc_data;
typedef struct s_data			t_data;
typedef struct s_varlist		t_varlist;
typedef struct s_pid_data		t_pid_data;
extern int						g_sig_offset;

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
	t_pid_data		*piddata;
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
void		init_signals(void);
void		interrupt_heredoc(int status);
void		interrupt_main(int status);
void		interrupt_exec(int status);
void		quit_exec(int status);
t_heredoc	*process_here_doc(char *limiter, t_data *data);
void		throw_lexer_error(t_data *data);

char		*ft_str_rejoin(char *stash, char *append);
void		copy_and_cat(char *out, char *cpy_src, char *cat_src, int len);

void		add_heredoc_node(t_heredoc *heredoc, t_data *data);
void		unlink_heredocs(t_data *data);
void		print_heredoc_warning(int index, char *limiter);

int			clean_exit(t_data *data, int exit_code);
char		*get_prompt(char *orig_prompt);
void		expand_string_var(t_data *data, char **str);

bool		var_in_str(char *s, char quote);
int			count_str_vars(char *str);

#endif
