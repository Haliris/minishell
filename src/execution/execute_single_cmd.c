/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:07:11 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/12 12:05:12 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_child(char *infile, char *outfile, int p_fd[])
{
	int	file_fd[2];
	int	dup_status;

	file_fd[0] = 0;
	file_fd[1] = 0;
	dup_status = 0;
	open_files(file_fd, outfile, infile);
	if (!file_fd[0] && p_fd[0] == TRUE)
		dup_status += dup2(p_fd[0], STDIN_FILENO);
	if (!file_fd[1] && p_fd[1] == TRUE)
		dup_status += dup2(p_fd[1], STDIN_FILENO);
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
	close(p_fd[0]);
	close(p_fd[1]);
	if (dup_status < 0)
		return ; //dup error
}

void	get_redirections(t_lex_parser *table, char redirection[])
{
	t_lex_parser		*roaming;
	t_redirect_table	*redir;
	char				*outfile;
	char				*infile;

	roaming = NULL;
	infile = NULL;
	outfile = NULL;
	go_to_first_table(roaming, table);
	while (roaming && roaming->type != TK_PARS_PIPE)
	{
		if (roaming->type == TK_PARS_REDIR)
		{
			redir = roaming->table;
			if (redir->type == TK_PARS_IN)
				infile = redir->redir_str;
			else if (redir->type == TK_PARS_OUT)
				outfile = redir->redir_str;
			roaming->type = TK_PARS_RESERVED;
		}
		roaming = roaming->next;
	}
	redirection[0] = infile;
	redirection[1] = outfile;
}

void	check_pipes(t_lex_parser *table, int pipe_status[])
{
	t_lex_parser	*roaming;

	roaming = table;
	go_to_first_table(roaming, table);
	if (roaming->prev && roaming->prev == TK_PARS_PIPE)
		pipe_status[0] == TRUE;
	while (roaming && roaming->next != TK_PARS_PIPE)
		roaming = roaming->next;
	if (roaming && roaming->next == TK_PARS_PIPE)
		pipe_status[1] = TRUE;
}

int	open_pipes(t_lex_parser *parsed, int p_fd[])
{
	int	has_pipe[2];

	has_pipe[0] = FALSE;
	has_pipe[1] = FALSE;
	check_pipes(parsed, has_pipe);
	if (pipe(p_fd) < 0)
		return (-1);
	if (has_pipe[0] == FALSE)
	{
		close(p_fd[0]);
		p_fd[0] = 0;
	}
	if (has_pipe[1] == FALSE)
	{
		close(p_fd[1]);
		p_fd[1] = 0;
	}
	return (SUCCESS);
}

int	redirect_parent(int p_fd[], char redir[])
{
	int	dup_status;

	dup_status = 0;
	if (p_fd[0])
		dup_status += dup2(p_fd[0], STDIN_FILENO);
	if (redir[0])
		close(redir[0]);
	if (redir[1])
		close(redir[1]);
	close(p_fd[0]);
	close(p_fd[1]);
	return (dup_status);
}

void	process_command(t_lex_parser *parsed, char **envp, int count)
{
	char		redir[2];
	int			p_fd[2];
	int			dup_status;
	t_cmd_table	*cmd_table;
	pid_t		pid_child;

	redir[0] = NULL;
	redir[1] = NULL;
	dup_status = 0;
	cmd_table = parsed->table;
	get_redirections(parsed, redir);
	if (open_pipes(parsed, p_fd) == -1)
		return ;
	pid_child = fork();
	if (pid_child < 0)
		return ;
	if (pid_child == 0)
	{
		redirect_child(redir[0], redir[1], p_fd);
		execute(cmd_table->cmd, envp);
	}
	else
	{
		dup_status += redirect_parent(p_fd, redir);
		if (dup_status < 0)
			return ;
	}
}
