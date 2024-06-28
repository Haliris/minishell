/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bento <bento@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:48:06 by bento             #+#    #+#             */
/*   Updated: 2024/06/28 18:01:07 by bento            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

bool	is_space(unsigned char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

t_token *lexer(char *input)
{
	t_token	*token;

	token = NULL;
	return (token);
}