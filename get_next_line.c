/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlakchai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 09:56:34 by codespace         #+#    #+#             */
/*   Updated: 2023/11/25 12:44:09 by tlakchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	get_content(t_gnl *gnl, int rd_bytes)
{
	t_list	*tmp;

	tmp = gnl->list;
	while (tmp != NULL)
	{
		if (tmp->cnt[0] == '\0')
		{
			rd_bytes = read(gnl->fd, tmp->cnt, BUFFER_SIZE);
			if (rd_bytes < 1)
				return (rd_bytes == 0);
			tmp->cnt[rd_bytes] = '\0';
		}
		if (gnl_strchr(tmp->cnt, '\n') != NULL)
			return (1);
		tmp->nx = gnl_lstnew(tmp->nx);
		if (tmp->nx == NULL)
			return (0);
		tmp = tmp->nx;
	}
	return (1);
}

char	*create_line(t_list *tmp)
{
	char	*line;
	size_t	i;
	size_t	len;

	len = 0;
	i = 0;
	while (tmp && tmp->cnt[i] != '\n' && tmp->cnt[i])
	{
		if (tmp->cnt[++i] == '\0' && tmp->nx)
		{
			tmp = tmp->nx;
			len += i;
			i = 0;
		}
	}
	len += i + (tmp->cnt[i] == '\n');
	if (len == 0)
		return (NULL);
	line = malloc(sizeof(char) * (len + 1));
	if (line == NULL)
		return (NULL);
	if (tmp->cnt[i] == '\n')
		line[len - 1] = '\n';
	line[len] = '\0';
	return (line);
}

char	*get_lines(t_gnl *gnl)
{
	char	*line;
	t_list	*tmp;
	size_t	i;
	size_t	len;

	line = create_line(gnl->list);
	if (line == NULL)
		return (NULL);
	len = 0;
	i = 0;
	while (gnl->list && gnl->list->cnt[i] != '\n' && gnl->list->cnt[i])
	{
		line[len++] = gnl->list->cnt[i++];
		if (!gnl->list->cnt[i])
		{
			tmp = gnl->list;
			gnl->list = gnl->list->nx;
			free(tmp);
			i = 0;
		}
	}
	if (gnl->list->cnt[i] == '\n')
		gnl_strcpy(gnl->list->cnt, gnl->list->cnt + i + 1);
	return (line);
}

char	*get_next_line(int fd)
{
	static t_gnl	gnl = {0, NULL};
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	gnl.fd = fd;
	gnl.list = gnl_lstnew(gnl.list);
	if (gnl.list == NULL)
		return (gnl_free(&gnl));
	if (!get_content(&gnl, 0))
		return (gnl_free(&gnl));
	line = get_lines(&gnl);
	if (line == NULL)
		return (gnl_free(&gnl));
	return (line);
}
