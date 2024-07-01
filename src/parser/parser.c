/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:21:33 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/01 16:58:07 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Parse tokens
//If command, recognize it as such
//Else
//Trim '' and ""
//Handle expansion if needed
//We might need lexstr to be **char instead of *char

#include "parser.h"
#include "lexer_dummy.h"

void	create_test_token()
{

}

//getenv()
bool	expand_variable(char *str)
{
	char	*value;
	char	**expanded_values;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			value = getenv(str);
			if (!value)
				return (-1);
			free(value);
		}
		i++;
	}
	return (1);
}

bool	call_builtin(char *str)
{

}

t_parsed	*parser_per_precedence(t_token *tokens_list, char **envp)
{
	t_token		*roaming;
	t_parsed	*parsed_table;

	parsed_table = ft_calloc(1, sizeof(t_parsed));
	if (!parsed_table)
		return (-1);
	roaming = tokens_list;
	while (roaming)
	{

		roaming = roaming->next;
	}
}

void	parser_per_token(t_token *tokens_list)
{
	t_token	*roaming;

	if (check_invalid_token(tokens_list))
		return (-1);
	roaming = tokens_list;
	while (roaming != NULL)
	{
		if (roaming->type == TK_INVALID)
			expand_variable(roaming->lexstr);
		else if (roaming->type == TK_BUILTIN)
			call_builtin(roaming->lexstr); //call or make?
		else if	(roaming->type == TK_KEYWORD)
			//use to find precedence
		else if (roaming->type == TK_PIPE)
			//Place indicators for redirection, flags for infile and outfile or here_doc
		else if (roaming->type == TK_STRING)
			//word to be passed as plain argument
		roaming = roaming->next;
	}
}
