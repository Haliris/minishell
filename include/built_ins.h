/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:58:36 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/17 19:39:39 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_INS_H
# define BUILT_INS_H
# include "minishell.h"

void	execute_builtin(char *cmd, t_data *data, int mode);

void	call_echo(t_data *data, char **cmd);
void	call_cd(t_data *data, char **cmd);
void	call_exit(t_data *data, char **cmd);
void	call_pwd(char **cmd);

#endif
