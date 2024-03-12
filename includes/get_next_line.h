/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:30:31 by nam-vu            #+#    #+#             */
/*   Updated: 2024/03/10 14:09:59 by dkoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# elif BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif
# include <unistd.h>
# include <stdlib.h>

typedef struct s_gnl_list
{
	char				*content;
	size_t				size;
	struct s_gnl_list	*next;
}	t_gnl_list;

typedef struct s_gnl
{
	char				buf[BUFFER_SIZE + 1];
	t_gnl_list			*lst;
	int					flush_flag;
	size_t				res_len;
}	t_gnl;

void	*gnl_memset(void *s, int c, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
char	*gnl_flush(t_gnl *data);
char	*parser(int fd, t_gnl *data, int *save);
char	*get_next_line(int fd, int *save);

size_t	gnl_strlen(const char *s, char mode);
char	*gnl_strdup(const char *s);
void	ft_lstadd_back(t_gnl *data, char *content);
void	ft_lstclear(t_gnl_list **lst, void (*del)(void*));
char	*ft_lstjoin(t_gnl *data, int *save);

#endif