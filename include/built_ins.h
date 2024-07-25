/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:58:36 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/25 13:13:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_INS_H
# define BUILT_INS_H
# include "minishell.h"

void	execute_builtin(t_vector *vector, t_data *data, int mode);

void	call_echo(t_data *data, char **cmd);
void	call_cd(t_data *data, char **cmd);
void	call_exit(t_data *data, char **cmd, int mode);
void	call_pwd(void);
void	call_export(t_data *data, char **cmd);
void	call_env(t_data *data, char **cmd);
void	call_unset(t_data *data, char **cmd);

char	*get_cwd(void);

#endif
