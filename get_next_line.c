/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 09:56:34 by codespace         #+#    #+#             */
/*   Updated: 2023/11/25 13:04:30 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	get_content(t_gnl *gnl, int rd_bytes)
{
	t_list	*tmp;

	if (gnl->list == NULL)
		gnl->list = gnl_lstnew();
	if (gnl->list == NULL)
		return (0);
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
		if (tmp->nx == NULL)
			tmp->nx = gnl_lstnew();
		if (tmp->nx == NULL)
			return (0);
		tmp = tmp->nx;
	}
	return (1);
}

char	*create_line(t_list *tmp, size_t i, size_t len)
{
	char	*line;

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

char	*get_lines(t_gnl *gnl, size_t i, size_t len, char **line)
{
	t_list	*tmp;

	*line = create_line(gnl->list, 0, 0);
	if (line == NULL)
		return (NULL);
	while (gnl->list && gnl->list->cnt[i] != '\n' && gnl->list->cnt[i])
	{
		(*line)[len++] = gnl->list->cnt[i++];
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
	return (*line);
}

char	*get_next_line(int fd)
{
	static t_gnl	gnl;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	gnl.fd = fd;
	if (!get_content(&gnl, 0))
		return (gnl_free(&gnl));
	if (get_lines(&gnl, 0, 0, &line) == NULL)
		return (gnl_free(&gnl));
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("test.txt", O_RDONLY);
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	return (0);
// }
