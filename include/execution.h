/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:53:36 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/28 17:20:37 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include "minishell.h"
# define PATH_ERROR 127
# define EXIT_FAILURE 1
# define CHILD 0
# define PARENT 1
# define BUILT_IN 2

typedef struct s_varlist		t_varlist;

typedef struct s_pid_data		t_pid_data;
typedef struct s_pid_data
{
	pid_t		pid;
	t_pid_data	*next;
}	t_pid_data;

void	handle_error(char *message, int code, t_data *data, char **cmd);
void	execute_cmd(t_vector *cmd_vector, t_data *data);
char	**build_env(t_varlist *vars);
int		count_commands(t_parser *data);

int		process_files(t_parser *table);
int		get_redirections(t_parser *roaming, char *redirection[]);
void	check_pipes(t_parser *table, int pipe_status[]);
int		add_pid_node(t_data *data, int pid);

int		execute_data(t_data *data);
char	**make_command_array(t_vector *vector);
int		execute_commands(t_data *data, int std_fd[]);
int		process_command(t_parser *p, t_data *data);
int		redir_child(t_parser *p, t_data *data, int p_fd[], int has_pipe[]);
char	*check_infiles(t_parser *parser);
void	throw_bad_file(t_data *data, char *bad_file);
int		redirect_parent(t_data *data, int p_fd[], int has_pipe[]);

#endif
