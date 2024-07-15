/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:14:25 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/15 19:30:35 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_error(char *message, int code)
{
	ft_putstr_fd(message, 2);
	ft_putchar_fd('\n', 2);
	exit(code);
}

void	trash(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	get_redirections(t_lex_parser *roaming, char *redirection[], int *heredoc_fd)
{
	char				*outfile;
	char				*infile;
	t_redirect_table	*redir;

	infile = NULL;
	outfile = NULL;
	if (roaming->type == TK_PARS_REDIR)
	{
		redir = roaming->table;
		if (redir->type == TK_PARS_HEREDOC)
			*heredoc_fd = dup(redir->heredoc_fd);
		else if (redir->type == TK_PARS_IN)
			infile = redir->redir_str;
		else if (redir->type == TK_PARS_OUT)
			outfile = redir->redir_str;
	}
	redirection[0] = infile;
	redirection[1] = outfile;
	return (*heredoc_fd);
}
