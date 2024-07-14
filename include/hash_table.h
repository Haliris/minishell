/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 13:55:56 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/14 13:48:03 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_TABLE_H
# define HASH_TABLE_H

# include "minishell.h"

# define HT_SIZE 8192

/* FNV-1a hashing */
# define FNV_OFFSET 14695981039346656037UL
# define FNV_PRIME 1099511628211UL

typedef struct s_ht_entry
{
	const char	*key;
	char		*value;
}	t_ht_entry;

typedef struct s_hash_table
{
	t_ht_entry	**entries;
	size_t		capacity;
	size_t		len;
}	t_hash_table;

t_hash_table	*ht_create(void);
uint64_t		hash_key(const char *key);
char			*ht_getval(t_hash_table *table, const char *key);
int				ht_set_entry(t_hash_table *table, t_ht_entry *entry);
void			ht_destroy_entry(t_ht_entry *entry);
void			ht_destroy(t_hash_table *table);
size_t			get_ht_idx(uint64_t hash, t_hash_table *table);
t_ht_entry		*create_entry(char *key, char *val);

#endif