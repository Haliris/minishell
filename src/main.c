/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:43:42 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/18 11:30:19 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_data(t_data *data)
{
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
		if (lexer(data))
		{
			if (invalid_tokens(data, data->token))
			{
				ft_printf("Error: Invalid token found\n");
				return (PANIC);
			}
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
		parse_data(&data);
		free_lexmem(&data);
		execute_data(&data);
		unlink_heredocs(&data);
	}
	if (prompt)
		free(prompt);
	return (clean_exit(&data, 0));
}
