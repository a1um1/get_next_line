/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:45:23 by codespace         #+#    #+#             */
/*   Updated: 2023/11/24 21:30:09 by codespace        ###   ########.fr       */
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

t_list	*gnl_lstnew(void)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (list == NULL)
		return (NULL);
	list->nx = NULL;
	list->cnt[0] = '\0';
	return (list);
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
