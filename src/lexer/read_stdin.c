/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_stdin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:29:27 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/06 19:34:47 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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
	char	*prompt;

	if (orig_prompt)
		free(orig_prompt);
	prompt = NULL;
	trunc_cwd = get_trunc_path();
	if (!trunc_cwd)
		return (NULL);
	prompt = ft_strjoin(trunc_cwd, " | minishell> ");
	free(trunc_cwd);
	return (prompt);
}

/* cc -lreadline -I./include -I./libft src/lexer/read_stdin.c 
	libft/ft_memmove.c 
	libft/ft_bzero.c libft/ft_strjoin.c libft/ft_strlen.c libft/ft_substr.c */
int	main(int argc, char **argv)
{
	t_data	data;
	char	*prompt;

	prompt = get_prompt(NULL);
	data.input = readline(prompt);
	while (data.input)
	{
		if (data.input)
			add_history(data.input);
		printf("%s\n", data.input);
		free(data.input);
		data.input = NULL;
		prompt = get_prompt(prompt);
		data.input = readline(prompt);
	}
	rl_clear_history();
	return (0);
}
