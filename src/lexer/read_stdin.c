/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_stdin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:29:27 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/06 16:50:42 by bthomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"


/* cc -lreadline -I./include -I./libft src/lexer/read_stdin.c libft/ft_memmove.c libft/ft_bzero.c */
int		main(int argc, char **argv)
{
	t_data	data;

	using_history();
	while ((data.input = readline("minishell> ")) != NULL)
	{
		if (data.input)
			add_history(data.input);
		printf("%s\n", data.input);
		free(data.input);
	}
	return (0);
}
