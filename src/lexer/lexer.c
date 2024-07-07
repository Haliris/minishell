/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:48:06 by bento             #+#    #+#             */
/*   Updated: 2024/07/07 12:34:48 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/* Unfortunately we're not allowed to use case statmements :( */
t_token	*lexer(char *input)
{
	t_token	*token;

	token = malloc(sizeof(t_token) * ft_strlen(input));
	if (!token)
		return (NULL);
}
