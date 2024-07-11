/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_pipe_lexstr.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:02:40 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/10 16:04:09 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	search_lexstr_for(t_token *roaming, char *temp_cmd)
{
	roaming = roaming->next;
	while (roaming && roaming->type != TK_PIPE)
	{
		if (roaming->type == TK_MARKED)
			temp_cmd = roaming->lexstr;
		roaming = roaming->next;
	}
}

void	search_lexstr_back(t_token *roaming, char *temp_cmd)
{
	roaming = roaming->prev;
	while (roaming && roaming->type != TK_PIPE)
	{
		if (roaming->type == TK_MARKED)
			temp_cmd = roaming->lexstr;
		roaming = roaming->prev;
	}
}

char	*get_pipe_cmd(t_token *tokens, int mode, t_lex_parser *parsed)
{
	t_token	*roaming;
	char	*temp_cmd;
	char	*cmd;

	roaming = tokens;
	temp_cmd = NULL;
	cmd = NULL;
	if (mode == FORWARD)
		search_lexstr_forward(roaming, temp_cmd);
	else
		search_lexstr_back(roaming, temp_cmd);
	if (!temp_cmd)
		return (NULL);
	cmd = ft_strdup(temp_cmd);
	if (!cmd)
		panic(parsed);
	return (cmd);
}
