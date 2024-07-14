/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:53:36 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/14 23:35:52 by marvin           ###   ########.fr       */
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

void	trash(char **array);
void	handle_error(char *message, int code);
void	execute_cmd(char *cmd, char **env, t_parser *data);

int		open_files(t_lex_parser *table);
void	get_redirections(t_lex_parser *table, char *redirection[]);
int		redirect_file(int file_fd[], int mode);

int		execute_data(t_parser *parsed_data, char **env);
int		execute_commands(t_parser *data, char **envp, int std_fds[]);
int		process_command(t_lex_parser *p, char **envp, t_parser *d, int std_fds[]);
int		redirect_child(t_lex_parser *p, int p_fd[], int has_pipe[]);

#endif
