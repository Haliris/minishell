/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:19:59 by jteissie          #+#    #+#             */
/*   Updated: 2024/06/17 10:51:39 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "execution.h"

void	redirect(int *p_fd, int *file_fd)
{
	close(p_fd[0]);
	close(file_fd[1]);
	close(file_fd[0]);
	dup2(p_fd[1], STDOUT_FILENO);
	close(p_fd[1]);
}

void	process_command(char *cmd, char **env, int *fd)
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
		redirect(p_fd, fd);
		execute(cmd, env);
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

int	execute_commands(int cmd_count, char *cmds[] char *envp[], int fds[])
{
	int		index;

	//file descriptors have to be parsed and properly sorted before being passed to this program
	index = 0;
	//legacy command for first command
	// process_command(av[index++], envp, fd_file, 0);
	while (index < cmd_count)
		process_command(cmds[index++], envp, fds[ADD_INDEX], 0);
	//legacy code for last command
	//process_command(av[ac - 2], envp, fd_file, LAST_FILE);
	wait_for_children(index);
	// Might need to close fds here too since they are inherited
	exit(EXIT_SUCCESS);
}
