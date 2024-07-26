/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:00:07 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/26 16:20:23 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define STD_FILEIN 3
#define STD_FILEOUT 4

int	redir_files(int file_fd[])
{
	int	dup_status;

	dup_status = 0;
	if (file_fd[0])
	{
		dup_status += dup2(file_fd[0], STDIN_FILENO);
		close(file_fd[0]);
		file_fd[0] = 0;
	}
	if (file_fd[1])
	{
		dup_status += dup2(file_fd[1], STDOUT_FILENO);
		close(file_fd[1]);
		file_fd[1] = 0;
	}
	return (dup_status);
}

int	open_files(char *redir[], int file_fd[], int *append)
{
	if (redir[0])
		file_fd[0] = open(redir[0], O_RDONLY);
	if (redir[1])
	{
		if (*append == TRUE)
			file_fd[1] = open(redir[1], O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (*append == FALSE)
			file_fd[1] = open(redir[1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	}
	*append = FALSE;
	if (file_fd[0] < 0 || file_fd[1] < 0)
		return (PANIC);
	redir[0] = NULL;
	redir[1] = NULL;
	return (SUCCESS);
}

int	process_files(t_parser *table)
{
	char			*redir[2];
	int				f_fd[2];
	int				append;
	t_parser		*roaming;

	f_fd[0] = 0;
	f_fd[1] = 0;
	redir[0] = NULL;
	redir[1] = NULL;
	roaming = table;
	while (roaming->prev && roaming->prev->type != TK_PARS_PIPE)
		roaming = roaming->prev;
	while (roaming && roaming->type != TK_PARS_PIPE)
	{
		if (roaming->type == TK_PARS_REDIR)
		{
			append = get_redirections(roaming, redir);
			if (open_files(redir, f_fd, &append) == PANIC
				|| redir_files(f_fd) < 0)
				return (-1);
		}
		roaming = roaming->next;
	}
	return (SUCCESS);
}

int	redirect_pipe(int p_fd[], int has_pipe[])
{
	int	dup_status;

	dup_status = 0;
	if (p_fd[0] != -1)
		close(p_fd[0]);
	if (has_pipe[1] == TRUE && p_fd[1] != -1)
	{
		dup_status += dup2(p_fd[1], STDOUT_FILENO);
		close(p_fd[1]);
	}
	return (dup_status);
}

char	*check_infiles(t_parser *parser)
{
	char				*bad_file;
	t_parser			*roaming;
	t_redirect_table	*redir;

	roaming = parser;
	bad_file = NULL;
	if (!roaming)
		return (bad_file);
	while (roaming->prev && roaming->prev->type != TK_PARS_PIPE)
		roaming = roaming->prev;
	while (roaming && roaming->type != TK_PARS_PIPE)
	{
		if (roaming->type == TK_PARS_REDIR)
		{
			redir = roaming->table;
			if (redir->type != TK_PARS_IN)
			{
				roaming = roaming->next;
				continue ;
			}
			if (access(redir->redir_str, F_OK) != 0)
			{
				bad_file = redir->redir_str;
				return (bad_file);
			}
		}
		roaming = roaming->next;
	}
	return (bad_file);
}

void	throw_bad_file(t_data *data, char *bad_file)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(bad_file, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	handle_error(NULL, EXIT_FAILURE, data, NULL);
}

int	redir_child(t_parser *p, t_data *data, int p_fd[], int has_pipe[])
{
	char	*bad_file;

	bad_file = NULL;
	close(STD_FILEIN);
	close(STD_FILEOUT);
	if (redirect_pipe(p_fd, has_pipe) < 0)
		return (PANIC);
	bad_file = check_infiles(p);
	if (bad_file)
		throw_bad_file(data, bad_file);
	if (process_files(p) < 0)
		return (PANIC);
	return (SUCCESS);
}

#undef STD_FILEIN
#undef STD_FILEOUT
