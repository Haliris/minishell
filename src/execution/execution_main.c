/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:19:59 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/10 14:35:30 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// Redirections are processed from left to right with the respective LAST one taking effect

void	execute_pipe(char cmds[], char **env, int index)
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
		redirect_pipe();
		execute(cmds[index], env);
	}
	else
	{
		close(p_fd[1]);
		if (index == 0)
			dup2(p_fd[0], STDIN_FILENO);
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
		execute_pipe(cmds, env, index);
		index++;
	}
}

void	process_command(t_lex_parser *parsed, char **env, int *child_count)
{
	if (parsed->type == TK_CMD)
	{
		execute_single_cmd(parsed, **env);
		*child_count = *child_count + 1;
	}
	else if (parsed->type == TK_PIPE)
	{
		process_pipe(parsed, **env);
		*child_count = *child_count + 2;
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
		else if (roaming->type == TK_CMD)
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
