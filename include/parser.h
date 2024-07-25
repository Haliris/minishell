/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:17:51 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/25 11:23:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"
# define SUCCESS 1
# define PANIC 0

typedef struct s_data		t_data;
typedef struct s_token		t_token;
typedef struct s_parser		t_parser;
typedef enum e_tokentype	t_tokentype;
typedef enum e_parsed_token
{
	TK_PARS_NULL,
	TK_PARS_CMD,
	TK_PARS_REDIR,
	TK_PARS_PIPE,
}	t_parsed_token;

typedef enum e_redir_token
{
	TK_PARS_IN,
	TK_PARS_OUT,
	TK_PARS_APPEND,
	TK_PARS_HEREDOC,
}	t_redir_token;

typedef struct s_vector
{
	char	*buffer;
	size_t	size;
	size_t	word_count;
}	t_vector;

typedef struct s_cmd_table
{
	t_vector	*cmd_buff;
}	t_cmd_table;

typedef struct s_redirect_table
{
	char			*redir_str;
	t_redir_token	type;
	int				heredoc;
}	t_redirect_table;
typedef struct s_parser
{
	void			*table;
	t_parsed_token	type;
	t_parser		*next;
	t_parser		*prev;
}	t_parser;

int				interprete_lexer(t_data *data);
int				build_redirect_table(t_parser *parsed, t_token *lexer);
char			*build_cmd_buffer(char *cmd_buff, t_token *roaming);
int				parsed_add_back(t_parser *p, void *t, t_parsed_token type);
void			free_parsed_mem(t_parser **data);
void			panic(t_parser *parsed);

#endif
