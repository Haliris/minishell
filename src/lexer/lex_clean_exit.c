/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_clean_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 12:30:45 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/15 18:28:35 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	free_strarray(char **array)
{
	size_t	i;

	i = 0;
	while (array && array[i])
		free(array[i++]);
	if (array)
		free(array);
}

void	free_tokens(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		if (token->lexstr)
			free(token->lexstr);
		if (token->path)
			free(token->path);
		free(token);
		token = NULL;
		token = tmp;
	}
}

void	free_lexmem(t_data *data)
{
	free_tokens(data->token);
	data->token = NULL;
	if (data->input)
	{
		free(data->input);
		data->input = NULL;
	}
}

int	lex_clean_exit(t_data *data, int exit_code)
{
	free_lexmem(data);
	rl_clear_history();
	return (exit_code);
}
