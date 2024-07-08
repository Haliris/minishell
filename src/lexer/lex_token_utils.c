/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_token_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 11:46:10 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/08 13:53:12 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*lex_get_last_token(t_data *data)
{
	while (data->token->next)
		data->token = data->token->next;
	return (data->token);
}

void	lex_add_token(t_data *data, t_token token)
{
	t_token	*last;

	if (!data->token)
	{
		data->token = &token;
		return ;
	}
	last = lex_get_last_token(data);
	last->next = &token;
	token.prev = last;
}

void	free_tokens(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		if (tmp->lexstr)
			free(tmp->lexstr);
	}
	token = NULL;
}

void	print_token(t_token *token)
{
	printf("Token type: %d\n", token->type);
	printf("Token lexstr: %s\n", token->lexstr);
}
