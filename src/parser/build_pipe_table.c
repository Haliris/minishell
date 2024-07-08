#include "minishell.h"
#include "lexer_dummy.h"

int	build_cmd1_str(t_token *lexer)
{
	t_token	*roaming;
	int		error;

	roaming = lexer;
	error = FALSE;
	if (roaming->type == TK_OPERATOR)
		return (error);
	roaming = roaming->prev;
	while (roaming->next->type != TK_EXECUTABLE)
	{
		if (roaming->type != TK_STRING && roaming->type != TK_EXECUTABLE)
		{
			error = TRUE;
			break;
		}
		roaming->next->type = TK_MARKED;
		roaming->next->lexstr = re_join_lexstr(roaming->next->lexstr, roaming->lexstr, BACKWARD);
		if (!roaming->prev)
		{
			roaming->type = TK_MARKED;
			break ;
		}
		roaming = roaming->prev;
	}
	return (error);
}

int	build_cmd2_str(t_token *lexer)
{
	t_token	*roaming;
	int		error;

	roaming = lexer;
	error = FALSE;
	if (roaming->type != TK_EXECUTABLE)
		error = TRUE;
	roaming->type = TK_MARKED;
	roaming = roaming->next;
	while (roaming && roaming->type == TK_STRING)
	{
		roaming->lexstr = re_join_lexstr(roaming->prev->lexstr, roaming->lexstr, FORWARD);
		roaming->type = TK_MARKED;
		if (!roaming->lexstr) //stupid safety logic, need better token removal
			break ;
		roaming = roaming->next;
	}
	return (error);
}

char	*get_cmd_lexstr(t_token *tokens, int mode)
{
	t_token	*roaming;

	roaming = tokens;
	if (mode == FORWARD)
		while (roaming->next && roaming->next->type == TK_MARKED)
			roaming = roaming->next;
	else
		while (roaming->prev && roaming->prev->type == TK_MARKED)
			roaming = roaming->prev;
	return (roaming->lexstr);
}

void	build_pipe_table(t_lex_parser *parsed, t_token *lexer)
{
	t_pipe_table	*pipe_table;
	int				error;

	error = FALSE;
	if (!lexer->prev)
		return ;
	pipe_table = ft_calloc(1, sizeof(t_pipe_table));
	if (!pipe_table)
		return ;
	pipe_table->cmd2 = NULL;
	if (build_cmd1_str(lexer->prev) == 1)
		error = TRUE;
	pipe_table->cmd1 = get_cmd_lexstr(lexer, BACKWARD);
	if (!lexer->next)
		while(!pipe_table->cmd2)
			pipe_table->cmd2 = get_next_line(STDIN_FILENO);
	else
		if (build_cmd2_str(lexer->next) == 1)
			error = TRUE;
	pipe_table->cmd2 = get_cmd_lexstr(lexer, FORWARD);
	parsed->table = pipe_table;
	if (error == TRUE)
		parsed_table_add_back(parsed, pipe_table, TK_INVALID);
	else
		parsed_table_add_back(parsed, pipe_table, TK_PIPE);
	lexer->type = TK_MARKED;
	reserve_token(lexer);
}
