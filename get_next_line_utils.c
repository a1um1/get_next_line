/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:45:23 by codespace         #+#    #+#             */
/*   Updated: 2023/11/25 17:39:07 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*gnl_free(t_gnl *gnl)
{
	t_list	*tmp;

	while (gnl->lst)
	{
		tmp = gnl->lst;
		gnl->lst = gnl->lst->nx;
		free(tmp);
	}
	return (NULL);
}

t_list	*gnl_lstnew(t_list **lst)
{
	t_list	*list;

	if (*lst != NULL)
		return (*lst);
	list = malloc(sizeof(t_list));
	if (list == NULL)
		return (NULL);
	list->nx = NULL;
	list->cnt[0] = '\0';
	list->len = 0;
	list->nl = 0;
	list->ofst = 0;
	*lst = list;
	return (list);
}

char	*gnl_strchr(const char *s1, int c)
{
	size_t	i;

	i = 0;
	while (s1[i] && s1[i] != c)
		i++;
	if (s1[i] == c)
		return (&(((char *)s1)[i]));
	return (NULL);
}

size_t	gnl_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (i);
}
