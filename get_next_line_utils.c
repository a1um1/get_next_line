/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlakchai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:45:23 by codespace         #+#    #+#             */
/*   Updated: 2023/11/25 12:42:13 by tlakchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*gnl_free(t_gnl *gnl)
{
	t_list	*tmp;

	while (gnl->list)
	{
		tmp = gnl->list;
		gnl->list = gnl->list->nx;
		free(tmp);
	}
	gnl->list = NULL;
	return (NULL);
}

t_list	*gnl_lstnew(t_list *list)
{
	t_list	*tmp;

	if (list != NULL)
		return (list);
	tmp = malloc(sizeof(t_list));
	if (tmp == NULL)
		return (NULL);
	tmp->nx = NULL;
	tmp->cnt[0] = '\0';
	return (tmp);
}

char	*gnl_strchr(const char *s1, int c)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s1[i] != c)
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
