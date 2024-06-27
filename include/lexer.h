/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:30:56 by bthomas           #+#    #+#             */
/*   Updated: 2024/06/27 20:05:20 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

/* To experiment with / discuss:
 *
 * Different schools of thought for a state-machine:
 * 		1. you can explicitely define states like the below
 * 			1A. you then need to define how to transition between them.
 *		2. you can have your functions be the states & calling them
 *			is transitioning.
 */

typedef enum e_tokentype
{
	TK_IDENTIFIER,
	TK_NUMBER,
	TK_OPERATOR,
	TK_STRING,
	TK_WHITESPACE
}	t_tokentype;

typedef enum e_state
{
	STATE_START,
	STATE_IN_IDENTIFIER,
	STATE_IN_NUMBER,
	STATE_IN_OPERATOR,
	STATE_IN_STRING,
	STATE_END
}	t_state;

typedef struct s_token
{
	t_tokentype	type;
	char		*lexstr;
}	t_token;

/* unsure if the below is feasible
typedef struct s_token
{
	t_tokentype	type;
	t_token		**sub_tokens;
	char		*lexstr;
}
*/

#endif
