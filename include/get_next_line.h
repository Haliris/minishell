/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:11:27 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/20 13:07:14 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

char	*get_next_line(int fd);
char	*fetch_line(char *line_stash, int fd, int *status);
char	*trim_buff(char *read_buff);
void	get_stash(char *stash, char *line);
int		find_eol(char *str);
void	copy_and_cat(char *out, char *cpy_src, char *cat_src);

#endif
