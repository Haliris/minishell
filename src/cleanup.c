/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 12:30:45 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/21 17:00:53 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	free_strarray(char **array)
{
	size_t	i;

	i = 0;
	while (array && array[i])
		free(array[i++]);
	if (array)
		free(array);
}

void	free_tokens(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		if (token->lexstr)
			free(token->lexstr);
		if (token->path)
			free(token->path);
		free(token);
		token = NULL;
		token = tmp;
	}
}

void	free_lexmem(t_data *data)
{
	free_tokens(data->token);
	data->token = NULL;
	if (data->input)
	{
		free(data->input);
		data->input = NULL;
	}
	if (data->prompt)
	{
		free(data->prompt);
		data->prompt = NULL;
	}
}

void	free_env(t_data *data)
{
	t_varlist	*curr;
	t_varlist	*next;

	if (!data->env_vars)
		return ;
	curr = data->env_vars;
	while (curr)
	{
		next = curr->next;
		if (curr->key)
		{
			free(curr->key);
			curr->key = NULL;
		}
		if (curr->val)
		{
			free(curr->val);
			curr->val = NULL;
		}
		free(curr);
		curr = next;
	}
}

int	clean_exit(t_data *data, int exit_code)
{
	free_lexmem(data);
	rl_clear_history();
	free_env(data);
	if (data->parsedata)
	{
		free_parsed_mem(&data->parsedata);
		free(data->parsedata);
	}
	if (data->heredata)
		unlink_heredocs(data);
	free(data->heredata);
	return (exit_code);
}
