/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_concat_tks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:23:45 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/30 12:44:05 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	delete_tk(t_token **head, t_token **tk)
{
	if (!head || !*head || !tk || !*tk)
		return ;
	if (*head == *tk)
		*head = (*tk)->next;
	if ((*tk)->prev)
		(*tk)->prev->next = (*tk)->next;
	if ((*tk)->next)
		(*tk)->next->prev = (*tk)->prev;
	if ((*tk)->lexstr)
		free((*tk)->lexstr);
	if ((*tk)->path)
		free((*tk)->path);
	free(*tk);
	*tk = NULL;
}

void	join_prev_tk(t_token *tk)
{
	char	*prev_str;
	char	*curr_str;
	char	*replace_str;

	if (!tk || !tk->prev)
		return ;
	if (tk->type == TK_PATH)
		curr_str = tk->path;
	else
		curr_str = tk->lexstr;
	if (tk->prev->type == TK_PATH)
		prev_str = tk->prev->path;
	else
		prev_str = tk->prev->lexstr;
	replace_str = ft_strjoin(prev_str, curr_str);
	if (tk->prev->path)
	{
		free(tk->prev->path);
		tk->prev->path = NULL;
	}
	free(tk->prev->lexstr);
	tk->prev->lexstr = replace_str;
	tk->prev->type = TK_STRING;
	tk->prev->endidx = tk->endidx;
}

static void	change_start_idx(t_data *data, t_token **token)
{
	char	quote;

	quote = 0;
	while ((*token)->startidx > 1)
	{
		if (in(data->input[(*token)->startidx], "\'\"")
			&& data->input[(*token)->startidx - 1] == '$')
			(*token)->startidx -= 1;
		if (in(data->input[(*token)->startidx - 1], "\'\""))
			quote = data->input[(*token)->startidx - 1];
		if (data->input[(*token)->startidx - 2] == quote)
		{
			(*token)->startidx -= 2;
			quote = 0;
		}
		else
			break ;
	}
}

static bool	joinable(t_token *prev_tk, t_token *curr_tk)
{
	if (!prev_tk || !curr_tk)
		return (false);
	if (prev_tk->type == TK_PIPE
		|| prev_tk->type == TK_REDIR
		|| prev_tk->type == TK_HEREDOC)
		return (false);
	if (curr_tk->type == TK_PIPE
		|| curr_tk->type == TK_REDIR
		|| curr_tk->type == TK_HEREDOC)
		return (false);
	if (prev_tk->endidx < curr_tk->startidx)
		return (false);
	if (!in_builtin(curr_tk, "echo"))
	{
		if (ft_strcmp(curr_tk->lexstr, "=") == 0
			|| ft_strcmp(prev_tk->lexstr, "=") == 0)
			return (false);
	}
	return (true);
}

void	join_tks(t_data *data)
{
	t_token	*next;
	t_token	*tk;
	t_token	*prev;

	tk = data->token;
	while (tk)
	{
		if (tk->type == TK_EXITSTATUS)
			expand_string_var(data, &tk->lexstr);
		next = tk->next;
		prev = tk->prev;
		change_start_idx(data, &tk);
		if (joinable(prev, tk))
		{
			join_prev_tk(tk);
			delete_tk(&data->token, &tk);
		}
		tk = next;
	}
}
