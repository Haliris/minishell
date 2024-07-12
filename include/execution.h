/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:53:36 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/12 15:35:16 by jteissie         ###   ########.fr       */
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
void	execute_cmd(char *cmd, char **env);

int		open_files(int file_fd[], t_lex_parser *table);
void	get_redirections(t_lex_parser *table, char *redirection[]);
void	go_to_first_table(t_lex_parser *roaming, t_lex_parser *parsed);

int		execute_commands(t_lex_parser *tables, char **envp);
int		process_command(t_lex_parser *parsed, char **envp);
int		redirect_child(int file_fd[], int p_fd[]);

#endif