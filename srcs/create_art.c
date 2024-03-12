/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_art.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 13:55:57 by dkoca             #+#    #+#             */
/*   Updated: 2024/03/12 21:51:47 by nam-vu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

void	split_and_add_node(t_trie *parent, t_entry entry, int next_index,
		int prefix)
{
	t_trie	*node;
	t_trie	*leaf;
	t_entry	next_entry;
	t_entry	node_entry;

	node_entry = entry;
	node_entry.start -= prefix;
	node_entry.end = entry.start;
	node_entry.value = NULL;
	node = ft_trie_new(node_entry, 2);
	leaf = ft_trie_new(entry, 0);
	parent->next[next_index]->entry.start += prefix;
	next_entry = parent->next[next_index]->entry;
	if (entry.key[entry.start] < next_entry.key[next_entry.start])
	{
		node->next[0] = leaf;
		node->next[1] = parent->next[next_index];
	}
	else
	{
		node->next[0] = parent->next[next_index];
		node->next[1] = leaf;
	}
	parent->next[next_index] = node;
}

void	split_edge(t_trie *parent, t_entry entry, int next_index, int prefix)
{
	t_trie	*node;
	t_entry	node_entry;

	node_entry = entry;
	node_entry.start -= prefix;
	node_entry.end = entry.start;
	node = ft_trie_new(node_entry, 1);
	parent->next[next_index]->entry.start += prefix;
	node->next[0] = parent->next[next_index];
	parent->next[next_index] = node;
}

void	add_node_curr(t_trie *temp, t_entry entry)
{
	int		i;
	int		pos;
	t_trie	**res;

	pos = -1;
	while (++pos < temp->child_num)
		if (entry.key[entry.start] 
			< temp->next[pos]->entry.key[temp->next[pos]->entry.start])
			break ;
	res = malloc((++temp->child_num) * sizeof(t_trie *));
	if (temp->child_num == 1)
		return (res[0] = ft_trie_new(entry, 0), temp->next = res, free(NULL));
	i = -1;
	while (++i < temp->child_num)
	{
		if (i == pos)
			res[i] = ft_trie_new(entry, 0);
		else
			res[i] = temp->next[i - ((i > pos) * 1)];
	}
	(free(temp->next), temp->next = res);
}

void	ft_trie_insert(t_trie *temp, t_entry entry)
{
	t_trie	*parent;
	int		next_index;
	int		prefix;
	int		index_save;
	int		int_utils[2];

	prefix = 0;
	next_index = search_match(temp->next, 0, temp->child_num - 1,
			entry.key[entry.start]);
	if (next_index < 0)
		return (add_node_curr(temp, entry));
	while (next_index >= 0)
	{
		parent = temp;
		temp = temp->next[next_index];
		prefix = common_prefix_len(&entry, &temp->entry);
		index_save = next_index;
		next_index = search_match(temp->next, 0, temp->child_num - 1,
				entry.key[entry.start]);
	}
	int_utils[0] = index_save;
	int_utils[1] = prefix;
	return (choose_operation(entry, temp, parent, int_utils));
}

void	ft_trie_search(t_trie *temp, t_entry entry)
{
	int		next_index;
	int		prefix;
	int		i;
	char	*key;

	next_index = search_match(temp->next, 0, temp->child_num - 1,
			entry.key[entry.start]);
	key = entry.key;
	i = 0;
	while (next_index >= 0)
	{
		temp = temp->next[next_index];
		prefix = common_prefix_len(&entry, &temp->entry);
		next_index = search_match(temp->next, 0, temp->child_num - 1,
				entry.key[entry.start]);
	}
	i = -1;
	if (entry.end == entry.start && temp->entry.end == entry.start
		&& temp->entry.value)
		while (temp->entry.value[++i])
			write(1, temp->entry.value + i, 1);
	else
		print_error(key, ++i);
}
