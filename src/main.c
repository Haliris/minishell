/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:43:42 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/22 16:37:01 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig_offset = 0;

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
	int	lex_status;

	if (valid_input(data->input, data))
	{
		lex_status = lexer(data);
		if (lex_status == LEXER_ERROR)
		{
			throw_lexer_error(data);
			return (PANIC);
		}
		else if (lex_status == HEREDOC_INTERRUPT)
		{
			free_lexmem(data);
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

	(void)argv;
	(void)argc;
	init(&data, env);
	data.prompt = NULL;
	while (1)
	{
		init_signals();
		data.prompt = get_prompt(data.prompt);
		if (get_input(&data, data.prompt) == PANIC)
			break ;
		if (g_sig_offset)
		{
			data.errcode = SIG_OFFSET + 2;
			g_sig_offset = 0;
		}
		if (tokenize_data(&data) == PANIC)
			continue ;
		parse_data(&data);
		free_lexmem(&data);
		execute_data(&data);
		unlink_heredocs(&data);
	}
	return (clean_exit(&data, data.errcode));
}
