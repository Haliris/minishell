/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_clean_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 12:30:45 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/08 16:19:08 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	free_lexmem(t_data *data)
{
	free_tokens(data->token);
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
