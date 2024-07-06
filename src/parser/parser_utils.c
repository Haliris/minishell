/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:00:24 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/05 15:24:12 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_dummy.h"


bool	check_invalid_token(t_token *tokens)
{
	t_token	*roaming;

	roaming = tokens;
	while (roaming)
	{
		if (roaming->type == TK_INVALID)
			return (TRUE);
		roaming = roaming->next;
	}
	return (FALSE);
}

void	remove_token(t_token *tokens)
{
	if (!tokens)
		return ; //wtf call, should not happen
	if (tokens->prev)
		tokens->prev->next = tokens->next;
	if (tokens->next)
		tokens->next->prev = tokens->prev;
	tokens->prev = NULL;
	tokens->next = NULL;
	tokens->type = TK_INVALID;
	tokens->lexstr = NULL;
	free(tokens);
}

char	*re_join_lexstr(char *lexstr, char *s2, int mode)
{
	char	*temp_new;
	char	*new;

	if (mode == FORWARD)
		temp_new = ft_strjoin(lexstr, " ");
	else
		temp_new = ft_strjoin(" ", lexstr);
	// free(lexstr);
	if (!temp_new)
		return (NULL);
	if (mode == FORWARD)
		new = ft_strjoin(temp_new, s2);	
	else
		new = ft_strjoin(s2, temp_new);
	free(temp_new);
	if (!new)
		return (NULL);
	return (new);
}

void	parsed_table_add_back(t_lex_parser *parsed, void *table, int type)
{
	t_lex_parser	*last;
	t_lex_parser	*new_node;

	if (!parsed->next)
	{
		parsed->table = table; //REFACTOR THIS SHIT JUST TAKE LSTADDBACK FROM LIBFT!!!
		return ;
	}
	new_node = ft_calloc(1, sizeof(t_lex_parser));
	if (!new_node)
		return ;
	new_node->table = table;
	new_node->type = type;
	new_node->next = NULL;
	last = parsed;
	while (last->next)
		last = last->next;
	last->next = new_node;
}