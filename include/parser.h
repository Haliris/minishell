/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:17:51 by jteissie          #+#    #+#             */
/*   Updated: 2024/07/01 16:52:41 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"

typedef struct s_parsed
{
	char		**parsed_str;
	int			precedence; //probably useless
	t_tokentype	type;
}	t_parsed;

bool	check_invalid_token(t_token *tokens);
#endif
