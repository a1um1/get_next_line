/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 09:53:55 by codespace         #+#    #+#             */
/*   Updated: 2023/11/25 17:03:24 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list	t_list;
struct s_list {
	char	cnt[BUFFER_SIZE + 1];
	size_t	len;
	size_t	nl;
	t_list	*nx;
};

typedef struct s_gnl	t_gnl;
struct s_gnl{
	int		fd;
	t_list	*list;
};

char		*get_next_line(int fd);
char		*get_lines(t_gnl *gnl, size_t i, size_t len, char **line);
char		*create_line(t_list *tmp, size_t i, size_t len, char **line);
char		get_content(t_gnl *gnl, t_list *tmp, int rd_bytes);

// Utils
t_list		*gnl_lstnew(t_list **lst);
size_t		gnl_strcpy(char *dst, const char *src);
char		*gnl_strchr(const char *s1, int c);
void		*gnl_free(t_gnl *gnl);

#endif
