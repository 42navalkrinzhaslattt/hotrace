/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 04:07:41 by nam-vu            #+#    #+#             */
/*   Updated: 2024/03/10 14:57:14 by dkoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

t_trie	*ft_trie_new(t_entry entry, int child_num)
{
	t_trie	*res;

	res = malloc(sizeof(t_trie));
	if (!res)
		return (NULL);
	res->entry.value = entry.value;
	res->entry.key = entry.key;
	res->entry.start = entry.start;
	res->entry.end = entry.end;
	res->child_num = child_num;
	res->next = NULL;
	if (child_num > 0)
		res->next = malloc(child_num * sizeof(t_trie *));
	return (res);
}

int	common_prefix_len(t_entry *prefix, t_entry *word)
{
	int	size;

	size = word->start;
	while (prefix->key[prefix->start] == word->key[size]
		&& prefix->start < prefix->end && size < word->end)
	{
		prefix->start++;
		size++;
	}
	return (size - word->start);
}

int	search_match(t_trie **arr, int start, int end, char key)
{
	int		comparison;
	int		middle;
	t_entry	entry;

	if (!arr || start > end)
		return (-1);
	middle = (start + end) / 2;
	entry = arr[middle]->entry;
	comparison = key - entry.key[entry.start];
	if (comparison > 0)
		return (search_match(arr, middle + 1, end, key));
	if (comparison < 0)
		return (search_match(arr, start, middle - 1, key));
	return (middle);
}

void	ft_clean_trie(t_trie *root)
{
	int	i;

	i = -1;
	while (root->next && ++i < root->child_num)
		ft_clean_trie(root->next[i]);
	if (root->entry.value)
	{
		free(root->entry.value);
		free(root->entry.key);
	}
	if (root->next)
		free(root->next);
	if (root)
		free(root);
}

void	print_error(char *key, int i)
{
	while (key[i])
		write(1, key + i++, 1);
	write(1, ": Not found.\n", 13);
}

// void	print_trie(t_trie *root, int depth)
// {
// 	int i;

// 	printf("depth = %d, key = %.*s\nvalue = %s\n", depth, root->entry.end
		// - root->entry.start, root->entry.key + root->entry.start,
		// root->entry.value);
// 	i = -1;
// 	while (root->next && ++i < root->child_num)
// 		print_trie(root->next[i], depth + 1);
// }
