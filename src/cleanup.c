/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 12:30:45 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/25 18:12:39 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	free_tokens(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		free_tk(token);
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

void	free_piddata(t_data *data)
{
	t_pid_data	*roaming;
	t_pid_data	*temp;

	if (!data->piddata)
		return ;
	roaming = data->piddata;
	while (roaming)
	{
		temp = roaming;
		roaming = roaming->next;
		free(temp);
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
	if (data->piddata)
		free_piddata(data);
	free(data->heredata);
	return (exit_code);
}
