/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:11:44 by bthomas           #+#    #+#             */
/*   Updated: 2024/07/14 15:06:40 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table.h"

void	ht_destroy_entry(t_ht_entry *entry)
{
	if (!entry)
		return ;
	if (entry->key)
	{
		free((void *)entry->key);
		entry->key = NULL;
	}
	if (entry->value)
	{
		free(entry->value);
		entry->value = NULL;
	}
	entry = NULL;
	free(entry);
}

void	ht_destroy(t_hash_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->capacity)
	{
		ht_destroy_entry(table->entries[i]);
		free(table->entries[i]);
		i++;
	}
	free(table->entries);
	free(table);
}

size_t	get_ht_idx(uint64_t hash, t_hash_table *table)
{
	return ((size_t)(hash & (uint64_t)(table->capacity - 1)));
}

t_ht_entry	*create_entry(char *key, char *val)
{
	t_ht_entry	*entry;

	entry = malloc(sizeof(t_ht_entry));
	if (!entry)
		return (NULL);
	entry->key = key;
	entry->value = val;
	return (entry);
}
