/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:30:56 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/20 14:23:20 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef struct s_data		t_data;
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
	TK_CMD,
	TK_RESERVED,
	TK_IN,
	TK_OUT,
	TK_OUT_APPEND,
}	t_tokentype;

typedef struct s_heredoc	t_heredoc;

typedef struct s_token
{
	t_tokentype	type;
	char		*lexstr;
	char		*path;
	t_heredoc	*heredoc;
	t_token		*next;
	t_token		*prev;
}	t_token;

int		lexer(t_data *data);
/* utilities - general */
char	*get_substr(char *input, size_t start_idx);
void	lex_add_token(t_data *data, t_token *token);
void	print_token(t_token *token);
char	*get_env_var(char *var_str);
char	*get_exec_path(char *input, size_t start_idx);
void	replace_str(char **old, char *new);

/* utilities - bools */
bool	is_builtin(char *input, size_t start_idx);
bool	is_space(unsigned char c);
bool	in(unsigned char c, const char *str);
bool	empty_quote(char *input, size_t start_idx);
bool	is_executable(char *input, size_t start_idx);
bool	is_delim(char c);

/* input validation */
bool	valid_input(char *input);
bool	invalid_tokens(t_data *data);

/* token retrieval */
t_token	*get_token(t_data *data, char *lexstr, char *path, t_tokentype type);
t_token	*lex_get_last_token(t_data *data);
t_token	*get_num_tk(t_data *data, char *input, size_t start_idx);
t_token	*get_num_tk(t_data *data, char *input, size_t start_idx);
t_token	*get_string_tk(t_data *data, char *input, size_t *start_idx);
t_token	*get_flag_tk(t_data *data, char *input, size_t start_idx);
t_token	*get_word_tk(t_data *data, char *input, size_t start_idx);
t_token	*get_redir_tk(t_data *data, char *input, size_t start_idx);
t_token	*get_exec_tk(t_data *data, char *input, size_t start_idx);
t_token	*get_path_tk(t_data *data, char *input, size_t start_idx);
int		get_heredoc_tk(t_token *roaming, t_data *data);

#endif
