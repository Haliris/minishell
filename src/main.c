/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:43:42 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/18 16:44:11 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_data(t_data *data)
{
	if (!data->parsedata)
	{
		data->parsedata = ft_calloc(1, sizeof(t_parser));
		if (!data->parsedata)
			return (PANIC);
	}
	if (data->token)
		if (interprete_lexer(data) == PANIC)
			return (PANIC);
	free_lexmem(data);
	return (SUCCESS);
}

int	tokenize_data(t_data *data)
{
	if (valid_input(data->input))
	{
		if (lexer(data) || invalid_tokens(data->token))
		{
			ft_printf("Error: Invalid token\n");
			return (PANIC);
		}
	}
	return (SUCCESS);
}

int	get_input(t_data *data, char *prompt)
{
	data->input = readline(prompt);
	if (data->input)
		add_history(data->input);
	else
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		return (PANIC);
	}
	return (SUCCESS);
}

int	main(int argc, char **argv, char **env)
{
	t_data			data;
	char			*prompt;

	(void)argv;
	(void)argc;
	init(&data, env);
	prompt = get_prompt(NULL);
	while (1)
	{
		prompt = get_prompt(prompt);
		if (get_input(&data, prompt) == PANIC || tokenize_data(&data) == PANIC)
			break ;
		if (collect_heredocs(&data) == PANIC)
			break ;
		free(prompt);
		prompt = NULL;
		parse_data(&data);
		free_lexmem(&data);
		execute_data(&data);
		unlink_heredocs(&data);
	}
	if (prompt)
		free(prompt);
	return (clean_exit(&data, data.errcode));
}
