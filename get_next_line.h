/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 09:53:55 by codespace         #+#    #+#             */
/*   Updated: 2023/11/24 20:27:51 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdbool.h>

typedef struct s_list	t_list;
struct s_list {
	char	cnt[BUFFER_SIZE + 1];
	t_list	*nx;
};

typedef struct s_gnl	t_gnl;
struct s_gnl{
	int		fd;
	t_list	*list;
};

char		*get_next_line(int fd);
t_list		*gnl_lstnew(void);
void		*gnl_free(t_gnl *gnl);
char		*get_lines(t_gnl *gnl);
char		*replace_new_line(char *str);
char		*gnl_strchr(const char *s1, int c);
char		*create_line(t_list *tmp);
size_t		gnl_strcpy(char *dst, const char *src);

#endif
