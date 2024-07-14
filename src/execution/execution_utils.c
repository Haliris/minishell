/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:14:25 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/14 17:33:24 by jteissie         ###   ########.fr       */
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

void	get_redirections(t_lex_parser *roaming, char *redirection[])
{
	char				*outfile;
	char				*infile;
	t_redirect_table	*redir;

	infile = NULL;
	outfile = NULL;
	if (roaming->type == TK_PARS_REDIR)
	{
		redir = roaming->table;
		if (redir->type == TK_PARS_IN)
			infile = redir->redir_str;
		else if (redir->type == TK_PARS_OUT)
			outfile = redir->redir_str;
	}
	redirection[0] = infile;
	redirection[1] = outfile;
}

int	redirect_files(int file_fd[])
{
	int	dup_status;

	dup_status = 0;
	if (file_fd[0])
	{
		dup_status += dup2(file_fd[0], STDIN_FILENO);
		close(file_fd[0]);
	}
	if (file_fd[1])
	{
		dup_status += dup2(file_fd[1], STDOUT_FILENO);
		close(file_fd[1]);
	}
	return (dup_status);
}

int	open_files(t_lex_parser *table)
{
	char	*redir[2];
	int		file_fd[2];

	file_fd[0] = 0;
	file_fd[1] = 0;
	t_lex_parser	*roaming;

	roaming = table;
	while (roaming && roaming->type != TK_PARS_PIPE)
	{
		if (roaming->type == TK_PARS_REDIR)
			get_redirections(roaming, redir);
		if (redir[0])
			file_fd[0] = open(redir[0], O_RDONLY);
		if (redir[1])
			file_fd[1] = open(redir[1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (file_fd[0] < 0 || file_fd[1] < 0)
			return (PANIC  );
		roaming = roaming->next;
		if (redirect_files(file_fd) == PANIC)
			return (PANIC);
		redir[0] = NULL;
		redir[1] = NULL;
	}
	return (SUCCESS);
}
