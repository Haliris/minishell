/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:07:11 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/10 14:06:44 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_files(int file_fd[], char *outfile, char *infile)
{
	if (infile)
		file_fd[0] = open(infile, O_CREAT | O_TRUNC, 064);
	if (outfile)
		file_fd[1] = open(outfile, O_CREAT | O_TRUNC, 064);
}

void	go_to_first_table(t_lex_parser *roaming, t_lex_parser *parsed)
{
	roaming = parsed;
	while (roaming->prev && roaming->prev->type != TK_PIPE)
		roaming = roaming->prev;
}

void	redirect(char *outfile, char *infile)
{
	int	file_fd[2];
	int	dup_status;

	file_fd[0] = 0;
	file_fd[1] = 0;
	dup_status = 0;
	open_files(file_fd, outfile, infile);
	if (file_fd[0] < 0 || file_fd[1] < 0)
	{
		if (file_fd[0])
			close(file_fd[0]);
		if (file_fd[1])
			close (file_fd[1]);
		return ; //open error
	}
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
	if (dup_status > 0)
		return ; //dup error
}

void	get_redirections(t_lex_parser *table, char *out, char *in)
{
	t_lex_parser		*roaming;
	t_redirect_table	*redir;

	roaming = NULL;
	go_to_first_table(roaming, table);
	while (roaming && roaming->type != TK_PIPE)
	{
		if (roaming->type == TK_REDIR)
		{
			redir = roaming->table;
			if (redir->type == TK_IN)
				in = redir->redir_str;
			else if (redir->type == TK_OUT)
				out = redir->redir_str;
			roaming->type = TK_RESERVED;
		}
		roaming = roaming->next;
	}
}

void	execute_single_cmd(t_lex_parser *parsed, char **envp)
{
	char		*infile;
	char		*outfile;
	t_cmd_table	*cmd_table;
	pid_t		pid_child;

	infile = NULL;
	outfile = NULL;
	cmd_table = parsed->table;
	get_redirections(parsed, outfile, infile);
	pid_child = fork();
	if (pid_child < 0)
		return ;
	if (pid_child == 0)
	{
		redirect(outfile, infile);
		execute(cmd_table->cmd, envp);
	}
}
