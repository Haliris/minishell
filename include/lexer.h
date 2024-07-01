/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:30:56 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/01 10:44:30 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

/* To experiment with / discuss:
 *
 * Different schools of thought for a state-machine:
 * 		1. you can explicitely define states like the below
 * 			1A. you then need to define how to transition between them.
 *		2. you can have your functions be the states & calling them
 *			is transitioning.
 */

typedef struct s_data
{
	char		*input;
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
	TK_WILDCARD,
	TK_BUILTIN,
	TK_ENVVAR,
	TK_EXECUTABLE,
	TK_IDENTIFIER,
	TK_NUMBER,
	TK_OPERATOR,
	TK_STRING,
	TK_KEYWORD,
	TK_REDIRECTION,
	TK_PIPE,
	TK_LOGICAL_AND,
	TK_LOGICAL_OR,
	TK_ASSIGNMENT
}	t_tokentype;

typedef enum e_state
{
	STATE_START,
	STATE_IN_IDENTIFIER,
	STATE_IN_NUMBER,
	STATE_IN_OPERATOR,
	STATE_IN_STRING,
	STATE_END
}	t_state;

/* subtoken used for subshell () - nested tokens*/
typedef struct s_token
{
	t_tokentype	type;
	char		*lexstr;
	t_token		**subtoken;
}	t_token;

# define MAX_INPUT_LEN 4096
# define INIT_BUFF_SIZE 1024

t_token	get_token(char *lexstr, t_tokentype type);

/* utilities */
bool	is_space(unsigned char c);
bool	in(unsigned char c, const char *str);
char	*get_substr(char *input, size_t start_idx);
bool	is_builtin(char *input, size_t start_idx);
t_token	get_num_tk(char *input, size_t start_idx);
t_token	get_op_tk(char *input, size_t start_idx);
t_token	get_executable(char *input, size_t start_idx);
t_token	get_string_tk(char *input, size_t start_idx);

#endif
