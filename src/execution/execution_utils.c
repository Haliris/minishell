/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:14:25 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/21 15:28:19 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define NOT_FOUND 127
#define CANNOT_EXECUTE 126

void	handle_error(char *message, int code, t_data *data)
{
	if (code == NOT_FOUND)
		message = "minishell: command not found";
	if (code == CANNOT_EXECUTE)
		message = "minishell: cannot execute command";
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	exit(clean_exit(data, code));
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

void	check_pipes(t_parser *table, int pipe_status[])
{
	t_parser	*roaming;

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

int	get_redirections(t_parser *roaming, char *redirection[])
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

#undef NOT_FOUND
#undef CANNOT_EXECUTE
