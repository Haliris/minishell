/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:30:56 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/07 17:09:04 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef struct s_token t_token;

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
	TK_NUMBER,
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

t_token	get_token(char *lexstr, t_tokentype type);
void	lex_add_token(t_data *data, t_token *token);
t_token	*lex_get_last_token(t_data *data);

/* utilities */
bool	is_space(unsigned char c);
bool	in(unsigned char c, const char *str);
char	*get_substr(char *input, size_t start_idx);
bool	is_builtin(char *input, size_t start_idx);
void	free_tokens(t_token *token);
int		lex_clean_exit(t_data *data, int exit_code);
bool	is_valid_input(char *input);

/* token retrieval */
t_token	get_num_tk(char *input, size_t start_idx);
t_token	get_string_tk(char *input, size_t start_idx);
t_token	get_num_tk(char *input, size_t start_idx);
t_token	get_string_tk(char *input, size_t start_idx);

#endif
