/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:43:42 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/20 15:50:16 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_signal	global_sig = {0};

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
	t_token	*roaming;

	if (valid_input(data->input))
	{
		if (lexer(data))
		{
			if (data->token)
				roaming = data->token;
			else
				roaming = NULL;
			while (roaming && roaming->next)
				roaming = roaming->next;
			ft_printf("minishell: syntax error near unexpected token ");
			if (roaming)
				ft_printf("'%s'\n", roaming->lexstr);
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
	char			*prompt;

	(void)argv;
	(void)argc;
	init(&data, env);
	prompt = get_prompt(NULL);
	while (1)
	{
		prompt = get_prompt(prompt);
		if (get_input(&data, prompt) == PANIC)
			break ;
		if (tokenize_data(&data) == PANIC)
			continue ;
		parse_data(&data);
		free_lexmem(&data);
		execute_data(&data);
		unlink_heredocs(&data);
	}
	if (prompt)
		free(prompt);
	return (clean_exit(&data, data.errcode));
}
