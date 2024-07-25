/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:30:56 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/25 18:20:14 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef struct s_data		t_data;
typedef enum e_tokentype
{
	TK_INVALID,
	TK_BUILTIN,
	TK_EXECUTABLE,
	TK_NUMBER,
	TK_PATH,
	TK_HEREDOC,
	TK_PIPE,
	TK_REDIR,
	TK_OPERATOR,
	TK_STRING,
	TK_EXITSTATUS,
	TK_CMD,
	TK_RESERVED,
}	t_tokentype;

typedef struct s_heredoc	t_heredoc;

typedef struct s_token
{
	t_tokentype	type;
	char		*lexstr;
	char		*path;
	char		quote;
	size_t		startidx;
	size_t		endidx;
	t_heredoc	*heredoc;
	t_token		*next;
	t_token		*prev;
}	t_token;

int			lexer(t_data *data);
/* utilities - general */
char		*get_substr(char *input, size_t start_idx);
void		lex_add_token(t_data *data, t_token *token);
void		print_token(t_token *token);
char		*get_env_var(char *var_str);
char		*get_exec_path(t_data *data, char *input, size_t start_idx);
void		replace_str(char **old, char *new);
size_t		get_str_tk_len(char *input, size_t startidx);
void		get_extended_str(char *input, size_t *startidx,
				char **outstr, size_t str_tk_len);
char		*extract_key_from_str(char *str, size_t start);
t_tokentype	get_last_tk_type(t_data *data);
void		remove_lim_node(t_token *node);
void		free_tk(t_token *tk);
int			concatenate_str_tks(t_data *data);

/* utilities - bools */
bool		is_builtin(char *input, size_t start_idx);
bool		is_space(unsigned char c);
bool		in(unsigned char c, const char *str);
bool		empty_quote(char *input, size_t start_idx);
bool		is_executable(t_data *data, char *input, size_t start_idx);
bool		is_delim(char c);
bool		invalid_path_char(char c);

/* input validation */
bool		valid_input(char *input, t_data *data);
bool		invalid_tokens(t_data *data);
bool		is_invalid_export(t_data *data, size_t curr_idx);

/* token retrieval */
t_token		*get_token(t_data *data, char *lexstr,
				char *path, t_tokentype type);
t_token		*lex_get_last_token(t_data *data);
t_token		*get_num_tk(t_data *data, char *input, size_t start_idx);
t_token		*get_num_tk(t_data *data, char *input, size_t start_idx);
t_token		*get_string_tk(t_data *data, size_t *start_idx);
t_token		*get_flag_tk(t_data *data, char *input, size_t start_idx);
t_token		*get_redir_tk(t_data *data, char *input, size_t start_idx);
t_token		*get_exec_tk(t_data *data, char *input, size_t start_idx);
t_token		*get_var_tk(t_data *data, char *input, size_t start_idx);
int			get_heredoc_tk(t_token *roaming, t_data *data);

#endif
