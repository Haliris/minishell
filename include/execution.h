/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:53:36 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/12 13:34:19 by jteissie         ###   ########.fr       */
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

char	*get_execpath(char **envp, char *av);
void	cat_slash(char **envp);
void	trash(char **array);
void	copycat_str(char *out, char *cpy_src, char *cat_src);
char	*get_path(char *av, char **env);
char	*ft_str_realloc_join(char *stash, char *add);
void	handle_error(char *message, int code);
void	try_absolute_path(char **command, char **env);
void	execute(char *av, char **env);

int		open_files(int file_fd[], char *outfile, char *infile);
void	go_to_first_table(t_lex_parser *roaming, t_lex_parser *parsed);

int		execute_commands(t_lex_parser *tables, char **envp);
void	process_command(t_lex_parser *parsed, char **envp);

#endif
