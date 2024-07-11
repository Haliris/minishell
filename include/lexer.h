/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:30:56 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/11 13:25:39 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

int		lexer(t_data *data);

/* utilities - general */
char	*get_substr(char *input, size_t start_idx);
void	free_tokens(t_token *token);
int		lex_clean_exit(t_data *data, int exit_code);
void	lex_add_token(t_data *data, t_token *token);
void	print_token(t_token *token);
void	free_lexmem(t_data *data);
void	free_strarray(char **array);
char	*get_env_var(char *var_str);
char	*get_exec_path(char *input, size_t start_idx);

/* utilities - bools */
bool	is_builtin(char *input, size_t start_idx);
bool	is_space(unsigned char c);
bool	in(unsigned char c, const char *str);
bool	empty_quote(char *input, size_t start_idx);
bool	is_executable(char *input, size_t start_idx);

/* input validation */
bool	valid_input(char *input);
bool	invalid_tokens(t_token *token);

/* token retrieval */
t_token	*get_token(t_data *data, char *lexstr, char *path, t_tokentype type);
t_token	*lex_get_last_token(t_data *data);
t_token	*get_num_tk(t_data *data, char *input, size_t start_idx);
t_token	*get_string_tk(t_data *data, char *input, size_t start_idx);
t_token	*get_num_tk(t_data *data, char *input, size_t start_idx);
t_token	*get_string_tk(t_data *data, char *input, size_t start_idx);
t_token	*get_flag_tk(t_data *data, char *input, size_t start_idx);
t_token	*get_word_tk(t_data *data, char *input, size_t start_idx);
t_token	*get_pipe_tk(t_data *data, char *input, size_t start_idx);
t_token	*get_redir_tk(t_data *data, char *input, size_t start_idx);
t_token	*get_exec_tk(t_data *data, char *input, size_t start_idx);
t_token	*get_path_tk(t_data *data, char *input, size_t start_idx);

#endif
