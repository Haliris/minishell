/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:58:36 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/16 18:41:39 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_INS_H
# define BUILT_INS_H
# include "minishell.h"

void	execute_builtin(char *cmd, char **env, t_parser *data);

void	call_echo(char **cmd);
void	call_cd(char **cmd);

#endif
