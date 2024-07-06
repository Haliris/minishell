#include "minishell.h"

int	build_cmd1_str(t_token *lexer)
{
	t_token	*roaming;
	t_token	*trash;
	int		error;

	roaming = lexer;
	error = FALSE;
	if (roaming->type == TK_EXECUTABLE)
		return (error);
	roaming = roaming->prev;
	while (roaming && roaming->next->type != TK_EXECUTABLE)
	{
		if (roaming->type != TK_STRING && roaming->type != TK_EXECUTABLE)
		{
			error = TRUE;
			break;
		}
		trash = roaming;
		roaming->next->lexstr = re_join_lexstr(roaming->next->lexstr, roaming->lexstr, BACKWARD);
		roaming = roaming->prev;
		remove_token(trash);
	}
	return (error);
}

int	build_cmd2_str(t_token *lexer)
{
	t_token	*roaming;
	t_token	*trash;
	int		error;

	roaming = lexer;
	error = FALSE;
	if (roaming->type != TK_EXECUTABLE)
		error = TRUE;
	roaming = roaming->next;
	while (roaming && roaming->type == TK_STRING)
	{
		trash = roaming->prev;
		roaming->lexstr = re_join_lexstr(roaming->prev->lexstr, roaming->lexstr, FORWARD);
		if (!roaming->lexstr) //stupid safety logic, need better token removal
			break ;
		roaming = roaming->next;
		remove_token(trash);
	}
	return (error);
}

void	build_pipe_table(t_lex_parser *parsed, t_token *lexer)
{
	t_pipe_table	*pipe_table;
	int				error;

	error = FALSE;
	if (!lexer->prev)
	{
		//bash: syntax error near unexpected token `|'
		return ;
	}
	if (!lexer->next)
	{
		//listen on stdin for input check bash behavior
		return ;
	}
	pipe_table = ft_calloc(1, sizeof(t_pipe_table));
	if (!pipe_table)
		return ;
	if (lexer->next->type != TK_EXECUTABLE || !lexer->prev) // lexer should handle these errors or return a specific token I can catch?
		error = TRUE;
	if (build_cmd1_str(lexer->prev) == 1)
		error = TRUE;
	pipe_table->cmd1 = lexer->prev->lexstr;
	if (build_cmd2_str(lexer->next) == 1)
		error = TRUE;
	pipe_table->cmd2 = lexer->next->lexstr;
	parsed->table = pipe_table;
	if (error == TRUE)
		parsed_table_add_back(parsed, pipe_table, TK_INVALID);
	else
		parsed_table_add_back(parsed, pipe_table, TK_PIPE);
	remove_token(lexer->next);
	remove_token(lexer->prev);
	// remove_token(lexer);
}