/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:17:51 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/05 15:45:29 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"

typedef enum e_parsed_token
{
	TK_CMD,
	TK_INFILE,
	TK_OUTFILE,
	TK_PIPE_IN,
	TK_PIPE_OUT,
}	t_parsed_token;

typedef struct s_solo_cmd
{
	char	*cmd;
}	t_solo_cmd;
typedef struct s_pipe_table
{
	char	*cmd1;
	char	*cmd2;
}	t_pipe_table;
typedef struct s_redirect_table
{
	char	*redir_str;
}	t_redirect_table;
typedef struct s_lex_parser t_lex_parser;
typedef struct s_lex_parser
{
	void			*table;
	t_parsed_token	type;
	t_lex_parser	*next;
}	t_lex_parser;

bool			check_invalid_token(t_token *tokens);
void			remove_token(t_token *tokens);
void			parsed_table_add_back(t_lex_parser *parsed, void *table, int type);
t_lex_parser	*interprete_lexer(t_token *tokens_list);

#endif
