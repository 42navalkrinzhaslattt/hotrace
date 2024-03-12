/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotrace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 01:50:08 by nam-vu            #+#    #+#             */
/*   Updated: 2024/03/10 13:55:54 by dkoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

int	main(void)
{
	t_entry	entry;
	t_trie	*trie;
	int		search_len;
	char	*temp;

	trie_init(&entry, &trie, &temp, &search_len);
	parse_dictionary(&entry, &trie, &temp, &search_len);
	parse_query(&entry, &trie, &temp, &search_len);
	ft_clean_trie(trie);
	return (0);
}
