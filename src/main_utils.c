/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:31:00 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/21 18:37:08 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	throw_lexer_error(t_data *data)
{
	t_token	*roaming;

	if (data->token)
		roaming = data->token;
	else
		roaming = NULL;
	while (roaming && roaming->next)
		roaming = roaming->next;
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	data->errcode = 2;
	if (roaming)
	{
		ft_putchar_fd('\'', 2);
		ft_putstr_fd(roaming->lexstr, 2);
		ft_putchar_fd('\'', 2);
	}
	ft_putchar_fd('\n', 2);
	free_lexmem(data);
}

void	free_strarray(char **array)
{
	size_t	i;

	i = 0;
	while (array && array[i])
		free(array[i++]);
	if (array)
		free(array);
}
