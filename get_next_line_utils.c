/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlakchai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:45:23 by codespace         #+#    #+#             */
/*   Updated: 2023/11/27 10:35:28 by tlakchai         ###   ########.fr       */
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
	list->ofst = 0;
	*lst = list;
	return (list);
}
