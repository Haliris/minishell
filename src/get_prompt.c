/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:41:50 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/19 11:07:29 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_trunc_path(void)
{
	char	*full_cwd;
	char	*trunc_cwd;
	size_t	i;
	size_t	len;
	int		depth;

	full_cwd = getcwd(NULL, 0);
	if (!full_cwd)
		return (NULL);
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
	trunc_cwd = get_trunc_path();
	if (!trunc_cwd)
		return (ft_strdup("minishell> "));
	prompt = ft_strjoin3("~", trunc_cwd, " | minishell> ");
	free(trunc_cwd);
	return (prompt);
}
