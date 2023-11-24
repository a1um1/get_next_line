/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 09:56:34 by codespace         #+#    #+#             */
/*   Updated: 2023/11/24 10:27:02 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	get_content(t_gnl *gnl)
{
	t_list	*list;
	int		read;

	list = gnl->list;
	while (list != NULL)
	{
		if (list->content[0] == '\0')
		{
		}
	}
}

t_list	*ft_lstnew(void)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (list == NULL)
		return (NULL);
	list->next = NULL;
	return (list);
}

char	*get_next_line(int fd)
{
	t_gnl	gnl;
	char	*line;

	if (gnl.fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	gnl.fd = fd;
	if (gnl.list == NULL)
		gnl.list = ft_lstnew();
	get_content(&gnl);
}

int	main(void)
{
	return (0);
}
