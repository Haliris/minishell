/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:14:25 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/12 12:04:42 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
// void	handle_error(char *message, int code)
// {
// 	ft_putstr_fd(message, 2);
// 	ft_putchar_fd('\n', 2);
// 	exit(code);
// }

// void	trash(char **array)
// {
// 	int	i;

// 	i = 0;
// 	if (!array)
// 		return ;
// 	while (array[i])
// 	{
// 		free(array[i]);
// 		i++;
// 	}
// 	free(array);
// }

void	open_files(int file_fd[], char *outfile, char *infile)
{
	if (infile)
		file_fd[0] = open(infile, O_CREAT | O_TRUNC, 064);
	if (outfile)
		file_fd[1] = open(outfile, O_CREAT | O_TRUNC, 064);
}

void	go_to_first_table(t_lex_parser *roaming, t_lex_parser *parsed)
{
	roaming = parsed;
	while (roaming->prev && roaming->prev->type != TK_PARS_PIPE)
		roaming = roaming->prev;
}

char	*ft_str_realloc_join(char *stash, char *add)
{
	char	*joined;

	if (!stash)
		return (NULL);
	joined = ft_calloc((ft_strlen(stash) + ft_strlen(add) + 1), sizeof(char));
	if (!joined)
		return (free(stash), NULL);
	copycat_str(joined, stash, add);
	return (free(stash), joined);
}

void	copycat_str(char *out, char *cpy_src, char *cat_src)
{
	size_t	i;
	int		src_i;

	src_i = 0;
	ft_strlcpy(out, cpy_src, ft_strlen(cpy_src) + 1);
	i = ft_strlen(out);
	while (cat_src[src_i])
		out[i++] = cat_src[src_i++];
	out[i] = '\0';
}
