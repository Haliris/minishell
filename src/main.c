/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:43:42 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/16 11:38:47 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init(t_data *data, char **env, t_parser *parser, t_heredoc_data *heredata)
{
	handle_signals();
	data->token = NULL;
	data->env = env;
	parser->node = NULL;
	heredata->heredoc = NULL;
	heredata->next = NULL;
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
	t_parser		parsed_data;
	t_heredoc_data	here_doc_data;
	char			*prompt;

	(void)argv;
	(void)argc;
	init(&data, env, &parsed_data, &here_doc_data);
	prompt = get_prompt(NULL);
	while (1)
	{
		prompt = get_prompt(prompt);
		if (get_input(&data, prompt) == PANIC || tokenize_data(&data) == PANIC)
			break ;
		if (collect_heredocs(&here_doc_data, &data) == PANIC)
			break ;
		parse_data(&data, &parsed_data);
		free_lexmem(&data);
		execute_data(&parsed_data, env);
		unlink_heredocs(&here_doc_data);
	}
	if (prompt)
		free(prompt);
	return (lex_clean_exit(&data, 0));
}
