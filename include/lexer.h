/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:30:56 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/11 09:35:54 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef struct s_token	t_token;

typedef struct s_data
{
	char		*input;
	char		**env;
	t_token		*token;
	size_t		buffer_size;
}	t_data;

/*
Identifiers:
	variables, functions, commands, labels
	typically names of commands.

Numbers:
	stand-alone numbers 

Operators:
	'+' '-' '*' '/' '%'

Keywords:
	if, then, else, while, do, for,
	break, continue, return, exit

Redirections:
	'>', '>>', '<', etc.

Pipe:
	'|'

Logical operators:
	AND	&&
	OR	||

Command separators:
	';'

Assignment:
	'='
*/

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
}	t_tokentype;

typedef struct s_token
{
	t_tokentype	type;
	char		*lexstr;
	t_token		*next;
	t_token		*prev;
}	t_token;

int		lexer(t_data *data);

/* utilities - general */
char	*get_substr(char *input, size_t start_idx);
void	free_tokens(t_token *token);
int		lex_clean_exit(t_data *data, int exit_code);
void	lex_add_token(t_data *data, t_token *token);
void	print_token(t_token *token);
void	free_lexmem(t_data *data);
int		init_lex(t_data *data, char **env);
void	free_strarray(char **array);
char	*get_env_var(char *var_str);
char	*get_exec_path(char *input, size_t start_idx);

/* utilities - bools */
bool	is_builtin(char *input, size_t start_idx);
bool	is_space(unsigned char c);
bool	in(unsigned char c, const char *str);
bool	empty_quote(char *input, size_t start_idx);
bool	is_executable(char *input, size_t start_idx);

/* input validation */
bool	valid_input(char *input);
bool	invalid_tokens(t_token *token);

/* token retrieval */
t_token	*get_token(t_data *data, char *lexstr, t_tokentype type);
t_token	*lex_get_last_token(t_data *data);
t_token	*get_num_tk(t_data *data, char *input, size_t start_idx);
t_token	*get_string_tk(t_data *data, char *input, size_t start_idx);
t_token	*get_num_tk(t_data *data, char *input, size_t start_idx);
t_token	*get_string_tk(t_data *data, char *input, size_t start_idx);
t_token	*get_flag_tk(t_data *data, char *input, size_t start_idx);
t_token	*get_word_tk(t_data *data, char *input, size_t start_idx);
t_token	*get_pipe_tk(t_data *data, char *input, size_t start_idx);
t_token	*get_redir_tk(t_data *data, char *input, size_t start_idx);
t_token	*get_exec_tk(t_data *data, char *input, size_t start_idx);
t_token	*get_path_tk(t_data *data, char *input, size_t start_idx);

#endif
