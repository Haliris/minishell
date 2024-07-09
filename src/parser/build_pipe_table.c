#include "minishell.h"
#include "lexer_dummy.h"

int	build_cmd1_str(t_token *lexer)
{
	t_token	*roaming;

	roaming = lexer;
	while (roaming->type != TK_RESERVED)
	{
		if (roaming->next->type != TK_PIPE)
			roaming->lexstr = re_join_lexstr(roaming->next->lexstr, roaming->lexstr, BACKWARD);
		if (!roaming->prev || roaming->type == TK_EXECUTABLE)
		 {
			roaming->type = TK_MARKED;
			break ;
		 }
		roaming->type = TK_MARKED;
		roaming = roaming->prev;
	}
}

void	build_cmd2_str(t_token *lexer)
{
	t_token	*roaming;

	roaming = lexer;
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

int	build_pipe_table(t_lex_parser *parsed, t_token *lexer)
{
	t_pipe_table	*pipe_table;

	if (check_parsing_error(lexer, TK_PIPE) == TRUE)
		return (PANIC);
	pipe_table = ft_calloc(1, sizeof(t_pipe_table));
	if (!pipe_table)
		return (PANIC);
	pipe_table->cmd1 = get_cmd_lexstr(lexer, BACKWARD);
	pipe_table->cmd2 = get_cmd_lexstr(lexer, FORWARD);
	parsed_table_add_back(parsed, pipe_table, TK_PIPE);
	lexer->type = TK_MARKED;
	reserve_token(lexer);
	return (SUCCESS);
}
