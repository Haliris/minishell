/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:25:06 by marvin            #+#    #+#             */
/*   Updated: 2024/07/17 22:25:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	count_vars(t_varlist *vars)
{
	int			count;
	t_varlist	*roaming;

	count = 0;
	roaming = vars;
	while (roaming)
	{
		count++;
		roaming = roaming->next;
	}
	return (count);
}

static void	panic_free(char **env)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	env = NULL;
}

static char	*assemble_strings(char *env, t_varlist *roaming)
{
	env = ft_strdup(roaming->key);
	env = ft_str_rejoin(env, "=");
	env = ft_str_rejoin(env, roaming->val);
	return (env);
}

char	**build_env(t_varlist *vars)
{
	char		**env;
	int			vars_count;
	int			i;
	t_varlist	*roaming;

	vars_count = count_vars(vars);
	roaming = vars;
	i = 0;
	env = ft_calloc(vars_count + 1, sizeof(char *));
	if (!env)
		return (NULL);
	while (roaming)
	{
		env[i] = assemble_strings(env[i], roaming);
		if (!env[i])
		{
			panic_free(env);
			break ;
		}
		roaming = roaming->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}
