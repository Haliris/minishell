/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:48:14 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/08 13:34:17 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/* catch non -n flags */

/* Add in orphan operators check, e.g., nothing before pipe */

static bool	unclosed_quotes(char *input, size_t len)
{
	size_t			i;
	unsigned char	quote;

	i = 0;
	while (i < len)
	{
		if (input[i] == "\"" || input[i] == "\'")
		{
			quote = input[i];
			i++;
			while (i < len && input[i] != quote)
				i++;
			if (i == len)
				return (true);
		}
		i++;
	}
	return (false);
}

static bool	special_chars(char *input, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (input[i] == "\\" || input[i] == ";" || !ft_isascii(input[i]))
			return (true);
		i++;
	}
	return (false);
}

/* Not interpret unclosed quotes or special characters which are not required 
by the subject such as \ (backslash) or ; (semicolon) */
bool	is_valid_input(char *input)
{
	size_t	len;

	len = ft_strlen(input);
	return (unclosed_quotes(input, len) || special_chars(input, len));
}
