/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:14:25 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/15 23:08:10 by marvin           ###   ########.fr       */
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

int	get_redirections(t_lex_parser *roaming, char *redirection[])
{
	char				*outfile;
	char				*infile;
	t_redirect_table	*redir;
	int					append;

	infile = NULL;
	outfile = NULL;
	append = FALSE;
	if (roaming->type == TK_PARS_REDIR)
	{
		redir = roaming->table;
		if (redir->type == TK_PARS_HEREDOC)
			infile = redir->redir_str;
		else if (redir->type == TK_PARS_IN)
			infile = redir->redir_str;
		else if (redir->type == TK_PARS_OUT || redir->type == TK_PARS_APPEND)
			outfile = redir->redir_str;
	}
	if (redir->type == TK_PARS_APPEND)
		append = TRUE;
	redirection[0] = infile;
	redirection[1] = outfile;
	return (append);
}
