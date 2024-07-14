/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 13:55:56 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/13 16:41:57 by bthomas          ###   ########.fr       */
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
	t_ht_entry	*entries;
	size_t		capacity;
	size_t		len;
}	t_hash_table;

t_hash_table	ht_create(void)
{
	t_hash_table	*table;

	table = malloc(sizeof(t_hash_table));
	if (!table)
		return (NULL);
	table->len = 0;
	table->capacity = HT_SIZE;
	table->entries = ft_calloc(table->capacity, sizeof(t_ht_entry));
	if (!table->entries)
	{
		free(table);
		return (NULL);
	}
	return (table);
}

void	ht_destroy_entry(t_ht_entry *entry)
{
	if (!entry)
		return ;
	if (entry->key)
	{
		free(entry->key);
		entry->key = NULL;
	}
	if (entry->value)
	{
		free(entry->value);
		entry->value = NULL;
	}
	free(entry);
	entry = NULL;
}

void	ht_destroy(t_hash_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->capacity)
	{
		ht_destroy_entry(table->entries[i]);
		i++;
	}
	free(table->entries);
	free(table);
}

uint64_t	hash_key(const char *key)
{
	uint64_t	hash;
	const char	*p;

	hash = FNV_OFFSET;
	p = key;
	while (*p)
	{
		hash ^= (uint64_t)(unsigned char)(*p);
		hash *= FNV_PRIME;
		p++;
	}
	return (hash);
}

size_t	get_ht_idx(uint64_t hash, t_hash_table *table)
{
	return ((size_t)(hash & (uint64_t)(table->capacity - 1)));
}

char	*ht_getval(t_hash_table *table, const char *key)
{
	uint64_t	hash;
	size_t		idx;

	hash = hash_key(key);
	idx = get_ht_idx(hash, table);
	while (table->entries[idx].key != NULL)
	{
		if (ft_strncmp(key, table->entries[idx].key) == 0
			&& ft_strlen(key) == ft_strlen(table->entries[idx].key))
			return (table->entries[idx].value);
		idx++;
		if (idx >= table->capacity)
			idx = 0;
	}
	return (NULL);
}

int	ht_set_entry(t_hash_table *table, t_ht_entry *entry)
{
	uint64_t	hash;
	size_t		idx;
	bool		looped;

	looped = false;
	hash = hash_key(entry->key);
	idx = get_ht_idx(hash, table);
	while (table->entries[idx])
	{
		if (ft_strcmp(entry->key, table->entries[idx]->key) == 0)
		{
			ht_destroy_entry(tables->entries[idx]);
			tables->entries[idx] = entry;
			return (0);
		}
		if (++idx >= table->capacity && !looped)
		{
			looped = true;
			idx = 0;
		}
		else if (idx >= table->capacity)
			return (1);
	}
	table->entries[idx] = entry;
	return (0);
}

#endif