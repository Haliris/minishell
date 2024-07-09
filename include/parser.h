/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:17:51 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/09 15:24:22 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"
# define FORWARD 1
# define BACKWARD 2
# define SUCCESS 1
# define PANIC 0

typedef struct s_lex_parser	t_lex_parser;
typedef enum e_parsed_token
{
	TK_CMD,
	TK_REDIR,
	TK_PIPE,
}	t_parsed_token;

typedef enum e_redir_token
{
	TK_IN,
	TK_OUT,
	TK_OUT_APPEND,
}	t_redir_token;
typedef struct s_cmd_table
{
	char	*cmd;
}	t_cmd_table;
typedef struct s_pipe_table
{
	char	*cmd1;
	char	*cmd2;
}	t_pipe_table;
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
}	t_lex_parser;

t_lex_parser	*interprete_lexer(t_token *tokens_list);
int				build_pipe_table(t_lex_parser *parsed, t_token *lexer);
int				build_redirect_table(t_lex_parser *parsed, t_token *lexer);

char			*re_join_lexstr(char *lexstr, char *s2, int mode);
int				check_remaining_tokens(t_token *tokens);
int				check_parsing_error(t_token *lexer, t_tokentype mode);

bool			check_invalid_token(t_token *tokens);
void			reserve_token(t_token *tokens);
int				parsed_add_back(t_lex_parser *parsed, void *table, int type);
#endif
