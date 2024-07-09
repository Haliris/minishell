/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:19:59 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/09 18:41:27 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect(int *p_fd, int *file_fd)
{
	close(p_fd[0]);
	close(file_fd[1]);
	close(file_fd[0]);
	dup2(p_fd[1], STDOUT_FILENO);
	close(p_fd[1]);
}

int	check_redir(t_lex_parser *parsed)
{
	int	redir_count;

	redir_count = 0;
	if (parsed->prev->type == TK_REDIR)
		redir_count++;
	if (parsed->next->type == TK_REDIR)
		redir_count++;
	return (redir_count);
}

void	process_command(t_lex_parser *parsed, char **env, int *child_count)
{
	int	pid_child;
	int	redirection;
	int	p_fd[2];

	redirection = check_redir(parsed);
	if (parsed->type == TK_CMD)
	{
		execute_single_cmd(parsed, **env);
		*child_count = *child_count + 1;
	}
	if (pipe(p_fd) == -1)
		handle_error("Could not open pipe for middle child", EXIT_FAILURE);
	pid_child = fork();
	if (pid_child < 0)
		handle_error("Could not fork middle child", EXIT_FAILURE);
	if (pid_child == 0)
	{
		redirect(p_fd, fd);
		execute(parsed, env);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], STDIN_FILENO);
		close(p_fd[0]);
	}
}

void	wait_for_children(int index)
{
	int	status;
	int	error_code;

	error_code = 0;
	while (index >= 0)
	{
		wait(&status);
		if (WEXITSTATUS(status) != 0)
		{
			error_code = WEXITSTATUS(status);
			ft_putstr_fd("Child exited early with error code: ", STDERR_FILENO);
			ft_putnbr_fd(error_code, STDERR_FILENO);
			ft_putchar_fd('\n', STDERR_FILENO);
			ft_putstr_fd(strerror(error_code), STDERR_FILENO);
			ft_putchar_fd('\n', STDERR_FILENO);
		}
		index--;
	}
	if (error_code)
		exit(EXIT_FAILURE);
}

//NEED SUPPORT FOR INFILES AND OUTFILES

int	execute_commands(int cmd_count, t_lex_parser *tables, char *envp[])
{
	int				child_count;
	t_lex_parser	*roaming;

	child_count = 0;
	roaming = tables;
	while (roaming)
	{
		if (roaming->type == TK_PIPE || roaming->type == TK_CMD)
			process_command(roaming, envp, &child_count);
		roaming = roaming->next;
	}
	wait_for_children(child_count);
	return (1);
}

int	count_commands(t_lex_parser *tables)
{
	int				cmd_count;
	t_lex_parser	*roaming;

	roaming = tables;
	cmd_count = 0;
	while (roaming)
	{
		if (roaming->type == TK_PIPE)
			cmd_count += 2;
		else if (roaming->TK_cmd_count)
			cmd_count++;
		roaming = roaming->next;
	}
	return (cmd_count);
}
void	process_tables(t_lex_parser *tables, char *envp[])
{
	int		cmd_count;
	int		pid_status;

	cmd_count = count_commands(tables);
	if (!cmd_count)
		return ;
	execute_commands(cmd_count, tables, envp);
}