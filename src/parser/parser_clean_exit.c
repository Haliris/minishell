
#include "minishell.h"


void	free_tables(t_lex_parser *r)
{
	t_cmd_table			*cmd_table;
	t_redirect_table	*redir_table;

	if (r->type == TK_PARS_CMD)
	{
		cmd_table = r->table;
		if (cmd_table)
			free(cmd_table->cmd);
		free(cmd_table);
		cmd_table = NULL;
	}
	if (r->type == TK_PARS_REDIR)
	{
		redir_table = r->table;
		if (redir_table->redir_str)
			free(redir_table->redir_str);
		free(redir_table);
		redir_table = NULL;
	}
}

void	free_parsed_mem(t_lex_parser *parsed)
{
	t_lex_parser	*roaming;
	t_lex_parser	*temp;

	roaming = parsed;
	while (roaming)
	{
		free_tables(roaming);
		temp = roaming;
		roaming = roaming->next;
		temp->type = 0;
		temp->next = NULL;
		temp->prev = NULL;
		free(temp);
	}
}