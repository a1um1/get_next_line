/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 09:56:34 by codespace         #+#    #+#             */
/*   Updated: 2023/11/25 18:03:58 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	get_content(t_gnl *gnl, t_list *tmp, int rd_bytes)
{
	while (tmp != NULL)
	{
		tmp->nl = 0;
		if (tmp->cnt[tmp->ofst] == '\0')
		{
			rd_bytes = read(gnl->fd, tmp->cnt, BUFFER_SIZE);
			if (rd_bytes < 1)
				return (rd_bytes == 0);
			tmp->cnt[rd_bytes] = '\0';
			tmp->len = rd_bytes;
			tmp->ofst = 0;
		}
		while (tmp->cnt[tmp->ofst + tmp->nl]
			&& tmp->cnt[tmp->ofst + tmp->nl] != '\n')
			tmp->nl++;
		if (tmp->cnt[tmp->ofst + tmp->nl] == '\n' || !gnl_lstnew(&(tmp->nx)))
			return (tmp->cnt[tmp->ofst + tmp->nl] == '\n' || tmp->nx != NULL);
		tmp = tmp->nx;
	}
	return (1);
}

char	*create_line(t_list *tmp, size_t i, size_t len, char **line)
{
	(void) i;
	while (tmp && tmp->cnt[tmp->ofst + tmp->nl] != '\n' && tmp->nx)
	{
		len += tmp->len - tmp->ofst;
		tmp = tmp->nx;
	}
	len += tmp->nl + (tmp->cnt[tmp->ofst + tmp->nl] == '\n');
	if (len == 0)
	{
		*line = NULL;
		return (NULL);
	}
	*line = malloc(sizeof(char) * (len + 1));
	if (*line == NULL)
		return (NULL);
	if (tmp->cnt[tmp->ofst + tmp->nl] == '\n')
		(*line)[len - 1] = '\n';
	(*line)[len] = '\0';
	return (*line);
}

char	*get_lines(t_gnl *gnl, size_t i, size_t len, char **line)
{
	t_list	*tmp;

	if (create_line(gnl->lst, 0, 0, line) == NULL)
		return (NULL);
	while (gnl->lst && gnl->lst->cnt[gnl->lst->ofst + i] != '\n'
		&& gnl->lst->cnt[gnl->lst->ofst + i])
	{
		(*line)[len++] = gnl->lst->cnt[gnl->lst->ofst + i];
		i++;
		if (!gnl->lst->cnt[gnl->lst->ofst + i])
		{
			tmp = gnl->lst;
			gnl->lst = gnl->lst->nx;
			free(tmp);
			i = 0;
		}
	}
	if (gnl->lst->cnt[gnl->lst->ofst + i] == '\n')
		gnl->lst->ofst += i + 1;
	return (*line);
}

char	*get_next_line(int fd)
{
	static t_gnl	gnl = {0, NULL};
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	gnl.fd = fd;
	if (gnl_lstnew(&(gnl.lst)) == NULL)
		return (gnl_free(&gnl));
	if (!get_content(&gnl, gnl.lst, 0))
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
