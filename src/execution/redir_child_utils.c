/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_child_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:27:26 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/26 16:32:50 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_infiles(t_parser *parser)
{
	char				*bad_file;
	t_parser			*roaming;
	t_redirect_table	*redir;

	roaming = parser;
	bad_file = NULL;
	if (!roaming)
		return (bad_file);
	while (roaming && roaming->type != TK_PARS_PIPE)
	{
		if (roaming->type == TK_PARS_REDIR)
		{
			redir = roaming->table;
			if (redir->type == TK_PARS_IN)
			{
				if (access(redir->redir_str, F_OK) != 0)
					bad_file = redir->redir_str;
			}
		}
		roaming = roaming->prev;
	}
	return (bad_file);
}

void	throw_bad_file(t_data *data, char *bad_file)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(bad_file, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	handle_error(NULL, EXIT_FAILURE, data, NULL);
}
