/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:14:25 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/18 14:35:57 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_error(char *message, int code)
{
	ft_putstr_fd(message, 2);
	ft_putchar_fd('\n', 2);
	exit(code);
}

void	trash(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	count_commands(t_parser *data)
{
	t_lex_parser	*roaming;
	int				cmd_count;

	roaming = data->node;
	cmd_count = 0;
	while (roaming)
	{
		if (roaming->type == TK_PARS_CMD)
		{
			cmd_count++;
		}
		roaming = roaming->next;
	}
	return (cmd_count);
}

void	check_pipes(t_lex_parser *table, int pipe_status[])
{
	t_lex_parser	*roaming;

	roaming = table;
	while (roaming->prev && roaming->prev->type != TK_PARS_PIPE)
		roaming = roaming->prev;
	if (roaming->prev && roaming->prev->type == TK_PARS_PIPE)
		pipe_status[0] = TRUE;
	while (roaming->next && roaming->next->type != TK_PARS_PIPE)
		roaming = roaming->next;
	if (roaming->next && roaming->next->type == TK_PARS_PIPE)
		pipe_status[1] = TRUE;
}

int	get_redirections(t_lex_parser *roaming, char *redirection[])
{
	char				*outfile;
	char				*infile;
	t_redirect_table	*redir;
	int					append;

	infile = NULL;
	outfile = NULL;
	append = FALSE;
	redir = NULL;
	if (roaming->type == TK_PARS_REDIR)
	{
		redir = roaming->table;
		if (redir->type == TK_PARS_HEREDOC)
			infile = redir->redir_str;
		else if (redir->type == TK_PARS_IN)
			infile = redir->redir_str;
		else if (redir->type == TK_PARS_OUT || redir->type == TK_PARS_APPEND)
			outfile = redir->redir_str;
	}
	if (redir->type == TK_PARS_APPEND)
		append = TRUE;
	redirection[0] = infile;
	redirection[1] = outfile;
	return (append);
}
