/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:43:42 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/15 19:23:21 by jteissie         ###   ########.fr       */
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

int	collect_heredocs(t_heredoc_data *here_data, t_data *data)
{
	t_token			*roaming;
	t_heredoc_data	*temp;
	t_heredoc_data	*new_node;

	roaming = data->token;
	while (roaming)
	{
		if (roaming->type == TK_HEREDOC)
		{
			if (!here_data->heredoc)
				here_data->heredoc = roaming->heredoc;
			else
			{
				temp = here_data;
				while (temp->next)
					temp = temp->next;
				new_node = ft_calloc(1, sizeof(t_heredoc_data));
				if (!new_node)
					return (PANIC);
				new_node->heredoc = roaming->heredoc;
				new_node->next = NULL;
				temp->next = new_node;
			}
		}
		roaming = roaming->next;
	}
	return (SUCCESS);
}

void	unlink_heredocs(t_heredoc_data *here_data)
{
	t_heredoc_data	*roaming;
	t_heredoc_data	*temp;
	int				index;

	if (!here_data->heredoc)
		return ;
	roaming = here_data;
	index = 0;
	while (roaming)
	{
		temp = roaming;
		if (ft_strlen(temp->heredoc->path))
			if (unlink(temp->heredoc->path) != 0)
				ft_printf("Error deleting file '%s': %s\n",
					temp->heredoc->path, strerror(errno));
		free(temp->heredoc);
		if (index > 0)
			free(temp);
		roaming = roaming->next;
	}
	here_data->heredoc = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_data			data;
	t_parser		parsed_data;
	t_heredoc_data	here_doc_data;
	char			*prompt;

	(void)argv;
	(void)argc;
	init(&data, env);
	prompt = get_prompt(NULL);
	here_doc_data.heredoc = NULL;
	here_doc_data.next = NULL;
	parsed_data.node = NULL;
	while (1)
	{
		prompt = get_prompt(prompt);
		if (get_input(&data) == PANIC)
			break ;
		if (tokenize_data(&data) == PANIC)
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
