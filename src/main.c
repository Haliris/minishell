/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:43:42 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/15 14:54:30 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init(t_data *data, char **env)
{
	handle_signals();
	data->token = NULL;
	data->env = env;
	return (0);
}

int	parse_data(t_data *data, t_parser *parsed_data)
{
	if (data->token)
		if (interprete_lexer(parsed_data, data->token) == PANIC)
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
			if (invalid_tokens(data->token))
			{
				ft_printf("Error: Invalid token found\n");
				return (PANIC);
			}
		}
	}
	return (SUCCESS);
}

int	get_input(t_data *data)
{
	data->input = readline("minishell>");
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
	t_parser		parsed_data;
	char			*prompt;

	(void)argv;
	(void)argc;
	init(&data, env);
	prompt = get_prompt(NULL);
	parsed_data.node = NULL;
	while (1)
	{
		prompt = get_prompt(prompt);
		if (get_input(&data) == PANIC)
			break ;
		if (tokenize_data(&data) == PANIC)
			break ;
		parse_data(&data, &parsed_data);
		execute_data(&parsed_data, env);
	}
	if (prompt)
		free(prompt);
	return (lex_clean_exit(&data, 0));
}
