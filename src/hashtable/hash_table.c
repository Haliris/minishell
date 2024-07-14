/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 16:42:49 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/14 17:06:38 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table.h"

t_hash_table	*ht_create(void)
{
	t_hash_table	*table;

	table = malloc(sizeof(t_hash_table));
	if (!table)
		return (NULL);
	table->len = 0;
	table->capacity = HT_SIZE;
	table->entries = ft_calloc(table->capacity, sizeof(t_ht_entry *));
	if (!table->entries)
	{
		free(table);
		return (NULL);
	}
	return (table);
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

char	*ht_getval(t_hash_table *table, const char *key)
{
	uint64_t	hash;
	size_t		idx;
	bool		looped;

	looped = false;
	hash = hash_key(key);
	idx = get_ht_idx(hash, table);
	while (1)
	{
		if (ft_strcmp(key, table->entries[idx]->key) == 0)
			return (table->entries[idx]->value);
		idx++;
		if (idx >= table->capacity && !looped)
		{
			looped = true;
			idx = 0;
		}
		else if (idx >= table->capacity)
			break ;
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
	while (table->entries[idx] && table->entries[idx]->key)
	{
		if (ft_strcmp(entry->key, table->entries[idx]->key) == 0)
		{
			ht_destroy_entry(table->entries[idx]);
			table->entries[idx] = entry;
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

/*
int	main(void)
{
	t_hash_table	*table;
	t_ht_entry		*entry;
	char			*key;
	char			*val;
	uint64_t		hash;
	size_t			idx;

	table = ht_create();
	if (!table)
		return (1);
	key = ft_strdup("Ben");
	val = ft_strdup("howdy");
	entry = create_entry(key, val);
	if (ht_set_entry(table, entry))
	{
		printf("Error: could not set entry.\n");
		ht_destroy(table);
		return (1);
	}
	hash = hash_key(key);
	idx = get_ht_idx(hash, table);
	printf("Key: '%s' idx: '%ld'\n", key, idx);
	printf("Getval test: key '%s' val '%s'\n", key, ht_getval(table, key));
	ht_destroy(table);
	return (0);
}
*/
