/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotrace.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 00:59:56 by nam-vu            #+#    #+#             */
/*   Updated: 2024/03/10 14:38:36 by dkoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOTRACE_H
# define HOTRACE_H

# include "get_next_line.h"

typedef struct s_entry
{
	char			*key;
	char			*value;
	int				start;
	int				end;
}					t_entry;

typedef struct s_trie
{
	t_entry			entry;
	struct s_trie	**next;
	int				child_num;
}					t_trie;

int					main(void);
t_trie				*ft_trie_new(t_entry entry, int child_num);
int					common_prefix_len(t_entry *prefix, t_entry *word);
int					search_match(t_trie **arr, int start, int end, char key);
void				ft_clean_trie(t_trie *root);
void				print_trie(t_trie *root, int depth);
void				print_error(char *key, int i);
void				choose_operation(t_entry entry, t_trie *temp,
						t_trie *parent, int *int_utils);
void				add_value_curr(t_trie *temp, t_entry entry);
void				parse_query(t_entry *entry, t_trie **trie, char **temp,
						int *search_len);
void				parse_dictionary(t_entry *entry, t_trie **trie, char **temp,
						int *search_len);
void				trie_init(t_entry *entry, t_trie **trie, char **temp,
						int *search_len);
void				ft_trie_search(t_trie *temp, t_entry entry);
void				ft_trie_insert(t_trie *temp, t_entry entry);
void				add_node_curr(t_trie *temp, t_entry entry);
void				split_edge(t_trie *parent, t_entry entry, int next_index,
						int prefix);

void				split_and_add_node(t_trie *parent, t_entry entry,
						int next_index, int prefix);
#endif