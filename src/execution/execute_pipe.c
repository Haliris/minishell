/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:29:41 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/10 17:31:50 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_pipe_redirections(int file_fd[], t_lex_parser *parser, int *pipe, int index)
{
	t_lex_parser		*roaming;
	t_redirect_table	*redir;
	char				*outfile;
	char				*infile;

	roaming = parser;
	outfile = NULL;
	infile = NULL;
	if (index == 0)
		go_to_first_table(roaming, parser->prev);
	if (index == 1)
		roaming = roaming->next;
	while (roaming && roaming->type != TK_PIPE)
	{
		if (roaming->type == TK_REDIR)
		{
			redir = roaming->table;
			if (redir->type == TK_IN)
				infile = redir->redir_str;
			else
				outfile = redir->redir_str;
		}
		roaming = roaming->next;
	}
	if (roaming->type == TK_PIPE)
		*pipe = TRUE;
	open_files(file_fd, outfile, infile);
}

void	redirect_pipe(int p_fd[], int index, t_lex_parser *parser)
{
	char	file_fd[2];
	int		dup_status;
	int		pipe_redir;

	close(p_fd[0]);
	pipe_redir = FALSE;
	dup_status = 0;
	file_fd[0] = 0;
	file_fd[1] = 0;
	get_pipe_redirections(file_fd, parser, &pipe_redir, index);
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
	else if (pipe_redir == TRUE)
		dup_status += dup2(p_fd[1], STDOUT_FILENO);
	close(p_fd[1]);
	if (dup_status < 0)
		return ; //dup_error;
}

void	execute_pipe(char cmds[], char **env, int index, t_lex_parser *parser)
{
	int	pid_child;
	int	p_fd[2];

	if (pipe(p_fd) == -1)
		handle_error("Could not open pipe for middle child", EXIT_FAILURE);
	pid_child = fork();
	if (pid_child < 0)
		handle_error("Could not fork middle child", EXIT_FAILURE);
	if (pid_child == 0)
	{
		redirect_pipe(p_fd, index, parser);
		execute(cmds[index], env);
	}
	else
	{
		close(p_fd[1]);
		if (dup2(p_fd[0], STDIN_FILENO) < 0)
		{
			close(p_fd[0]);
			return ; //dup error
		}
		close(p_fd[0]);
	}
}

void	process_pipe(t_lex_parser *parser, char **env)
{
	char			cmds[2];
	t_pipe_table	*pipe_table;
	int				index;

	index = 0;
	pipe_table = parser->table;
	if (pipe_table->cmd1)
		cmds[0] == pipe_table->cmd1;
	if (pipe_table->cmd2)
		cmds[1] == pipe_table->cmd2;
	while (index < 2)
	{
		execute_pipe(cmds, env, index, parser);
		index++;
	}
}
