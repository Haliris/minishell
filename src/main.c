/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:43:42 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/21 17:33:55 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_signal	g_sig = {0};

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

	if (valid_input(data->input, data))
	{
		if (lexer(data))
		{
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





#include <stdio.h>

int	main(int argc, char **argv, char **env)
{
	t_data			data;
	char			*prompt;

	(void)argv;
	(void)argc;
	init(&data, env);
	prompt = NULL;
	while (1)
	{
		init_signals();
		printf("g_sig.sigoffset: %d\n", g_sig.sigoffset);
		if (g_sig.sigoffset)
		{
			data.errcode = SIG_OFFSET + 2;
			g_sig.sigoffset = 0;
		}
		printf("errcode before get_prompt:%d\n", data.errcode);
		prompt = get_prompt(prompt);
		if (get_input(&data, prompt) == PANIC)
			break ;
		if (tokenize_data(&data) == PANIC)
			continue ;
		parse_data(&data);
		free_lexmem(&data);
		execute_data(&data);
		printf("errcode after execute:%d\n", data.errcode);
		unlink_heredocs(&data);
	}
	if (prompt)
		free(prompt);
	printf("errcode before exit:%d\n", data.errcode);
	return (clean_exit(&data, data.errcode));
}
