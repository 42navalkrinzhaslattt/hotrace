/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 13:52:25 by dkoca             #+#    #+#             */
/*   Updated: 2024/03/10 14:38:54 by dkoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

void	trie_init(t_entry *entry, t_trie **trie, char **temp, int *search_len)
{
	entry->key = "";
	entry->value = NULL;
	entry->start = 0;
	entry->end = 1;
	*trie = ft_trie_new(*entry, 0);
	*temp = get_next_line(0, &entry->end);
	entry->key = *temp;
	if (entry->key)
		entry->key[--(entry->end)] = 0;
	*temp = get_next_line(0, search_len);
	entry->value = *temp;
}

void	parse_dictionary(t_entry *entry, t_trie **trie, char **temp,
		int *search_len)
{
	while (entry->key && entry->value)
	{
		ft_trie_insert(*trie, *entry);
		*temp = get_next_line(0, &entry->end);
		entry->key = *temp;
		if (entry->key && entry->key[0] == '\n')
		{
			free(entry->key);
			break ;
		}
		if (entry->key)
			entry->key[--(entry->end)] = 0;
		*temp = get_next_line(0, search_len);
		entry->value = *temp;
	}
}

void	parse_query(t_entry *entry, t_trie **trie, char **temp, int *search_len)
{
	*temp = get_next_line(0, search_len);
	while (*temp)
	{
		entry->key = *temp;
		entry->end = *search_len;
		entry->value = NULL;
		entry->key[--(entry->end)] = 0;
		ft_trie_search(*trie, *entry);
		free(*temp);
		*temp = get_next_line(0, search_len);
	}
}

void	add_value_curr(t_trie *temp, t_entry entry)
{
	if (temp->entry.value)
		write(2, "Key already existing\n", 21);
	else
		temp->entry.value = entry.value;
}

void	choose_operation(t_entry entry, t_trie *temp, t_trie *parent,
		int *int_utils)
{
	int	cmp[2];

	cmp[0] = (entry.end == entry.start);
	cmp[1] = (temp->entry.end == entry.start);
	if (!cmp[0] && cmp[1])
		return (add_node_curr(temp, entry));
	else if (cmp[0] && cmp[1])
		return (add_value_curr(temp, entry));
	else if (cmp[0] && !cmp[1])
		return (split_edge(parent, entry, int_utils[0], int_utils[1]));
	return (split_and_add_node(parent, entry, int_utils[0], int_utils[1]));
}
