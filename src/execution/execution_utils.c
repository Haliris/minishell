/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:14:25 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/26 15:29:04 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_error(char *message, int code, t_data *data, char **cmd)
{
	if (code == NOT_FOUND)
		message = ": command not found";
	if (code == CANNOT_EXECUTE)
		message = ": cannot execute command";
	if (message)
		ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (cmd && cmd[0])
		ft_putstr_fd(cmd[0], STDERR_FILENO);
	if (message)
	{
		ft_putstr_fd(message, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	if (cmd)
		free_strarray(cmd);
	exit(clean_exit(data, code));
}

int	redirect_parent(int p_fd[])
{
	int	status;

	status = SUCCESS;
	if (p_fd[0] != -1)
	{
		if (dup2(p_fd[0], STDIN_FILENO) < 0)
			status = PANIC;
		close(p_fd[0]);
	}
	if (p_fd[1] != -1)
		close(p_fd[1]);
	return (status);
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

int	add_pid_node(t_data *data, int pid)
{
	t_pid_data	*node;
	t_pid_data	*roaming;

	roaming = data->piddata;
	node = ft_calloc(1, sizeof(t_pid_data));
	if (!node)
		return (PANIC);
	node->pid = pid;
	node->next = NULL;
	if (!roaming)
		data->piddata = node;
	else
	{
		while (roaming->next)
			roaming = roaming->next;
		roaming->next = node;
	}
	return (SUCCESS);
}
