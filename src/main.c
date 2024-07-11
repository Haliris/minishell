/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:43:42 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/11 13:24:24 by bthomas          ###   ########.fr       */
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

char	*get_trunc_path(void)
{
	char	*full_cwd;
	char	*trunc_cwd;
	size_t	i;
	size_t	len;
	int		depth;

	full_cwd = getcwd(NULL, 0);
	len = ft_strlen(full_cwd);
	i = len;
	depth = 0;
	while (--i > 0 && depth < 2)
		if (full_cwd[i] == '/')
			depth++;
	if (i == 0)
		return (full_cwd);
	trunc_cwd = ft_substr(full_cwd, i + 1, len - i - 1);
	free(full_cwd);
	return (trunc_cwd);
}

char	*get_prompt(char *orig_prompt)
{
	char	*trunc_cwd;
	char	*pre_prompt;
	char	*prompt;

	if (orig_prompt)
		free(orig_prompt);
	pre_prompt = NULL;
	trunc_cwd = get_trunc_path();
	if (!trunc_cwd)
		return (ft_strdup("minishell> "));
	pre_prompt = ft_strjoin(trunc_cwd, " | minishell> ");
	free(trunc_cwd);
	if (!pre_prompt)
		return (NULL);
	prompt = ft_strjoin("~", pre_prompt);
	free(pre_prompt);
	return (prompt);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	char	*prompt;

	(void)argv;
	init(&data, env);
	prompt = get_prompt(NULL);
	data.input = readline(prompt);
	while (data.input)
	{
		if (data.input)
			add_history(data.input);
		if (valid_input(data.input))
			if (lexer(&data))
				if (invalid_tokens(data.token))
					printf("Error: Invalid token found\n");
		free_lexmem(&data);
		prompt = get_prompt(prompt);
		data.input = readline(prompt);
	}
	if (prompt)
		free(prompt);
	return (0);
}
