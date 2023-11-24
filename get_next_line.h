/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 09:53:55 by codespace         #+#    #+#             */
/*   Updated: 2023/11/24 15:11:52 by codespace        ###   ########.fr       */
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
t_list		*ft_lstnew(void);
void		*free_all(t_gnl *gnl);
char		*get_line(t_gnl *gnl);
char		*replace_new_line(char *str);

#endif
