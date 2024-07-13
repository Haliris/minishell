/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:17:51 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/12 18:55:02 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"
# define SUCCESS 1
# define PANIC 0

typedef struct s_token		t_token;
typedef struct s_lex_parser	t_lex_parser;
typedef enum e_tokentype	t_tokentype;
typedef enum e_parsed_token
{
	TK_PARS_CMD,
	TK_PARS_REDIR,
	TK_PARS_PIPE,
}	t_parsed_token;

typedef enum e_redir_token
{
	TK_PARS_IN,
	TK_PARS_OUT,
	TK_PARS_OUT_APPEND,
}	t_redir_token;

typedef struct s_cmd_table
{
	char	*cmd;
}	t_cmd_table;
typedef struct s_redirect_table
{
	char			*redir_str;
	t_redir_token	type;
}	t_redirect_table;

typedef struct s_lex_parser
{
	void			*table;
	t_parsed_token	type;
	t_lex_parser	*next;
	t_lex_parser	*prev;
}	t_lex_parser;

typedef struct s_parsed_data
{
	t_lex_parser	*node;
}	t_parser;

int				interprete_lexer(t_parser *data, t_token *tokens_list);
int				build_redirect_table(t_lex_parser *parsed, t_token *lexer);

bool			check_invalid_token(t_token *tokens);
int				parsed_add_back(t_lex_parser *parsed, void *table, t_parsed_token type);
void			free_parsed_mem(t_parser *data);

#endif
