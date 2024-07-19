/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_token_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 11:46:10 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/19 18:06:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*get_token(t_data *data, char *lexstr, char *path, t_tokentype type)
{
	t_token	*token;

	if (data->token && type == TK_PIPE)
	{
		token = data->token;
		while (token->next)
			token = token->next;
		if (token->type == TK_PIPE || token->type == TK_REDIR)
			return (NULL);
	}
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
	{
		write(2, "Error: bad malloc\n", 19);
		exit(clean_exit(data, 1));
	}
	token->lexstr = lexstr;
	token->path = path;
	token->type = type;
	token->next = NULL;
	token->prev = NULL;
	token->heredoc = NULL;
	return (token);
}

t_token	*lex_get_last_token(t_data *data)
{
	t_token	*curr_tk;

	if (!data->token)
		return (NULL);
	curr_tk = data->token;
	while (curr_tk && curr_tk->next)
		curr_tk = curr_tk->next;
	return (curr_tk);
}

void	lex_add_token(t_data *data, t_token *token)
{
	t_token	*last;

	if (!token)
		return ;
	if (!data->token)
	{
		data->token = token;
		return ;
	}
	last = lex_get_last_token(data);
	if (last)
	{
		last->next = token;
		token->prev = last;
	}
	else
		data->token = token;
}

void	print_token(t_token *token)
{
	if (!token)
		return ;
	ft_printf("Token type: %d\n", token->type);
	ft_printf("Token lexstr: [%s]\n", token->lexstr);
	ft_printf("Token path: %s\n", token->path);
	if (token->heredoc)
		ft_printf("Heredoc path: %s\n", token->heredoc->path);
}
