/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlakchai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 09:56:34 by codespace         #+#    #+#             */
/*   Updated: 2023/11/27 10:35:46 by tlakchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>

char	get_content(t_gnl *gnl, t_list *tmp, int rd_bytes, size_t i)
{
	while (tmp)
	{
		if (!tmp->cnt[tmp->ofst])
		{
			rd_bytes = read(gnl->fd, tmp->cnt, BUFFER_SIZE);
			if (rd_bytes < 1)
				return (rd_bytes == 0);
			tmp->cnt[rd_bytes] = '\0';
			tmp->ofst = 0;
		}
		i = tmp->ofst;
		while (tmp->cnt[i] && tmp->cnt[i] != '\n')
			i++;
		gnl->is_nl = tmp->cnt[i] == '\n';
		gnl->line_len += i - tmp->ofst + gnl->is_nl;
		if (gnl->is_nl)
			return (1);
		if (!gnl_lstnew(&(tmp->nx)))
			return (0);
		tmp = tmp->nx;
	}
	return (1);
}

char	*create_line(t_gnl *gnl, char **line)
{
	if (!gnl->line_len)
		return (NULL);
	*line = malloc(sizeof(char) * (gnl->line_len + 1));
	if (*line == NULL)
		return (NULL);
	if (gnl->is_nl)
		(*line)[gnl->line_len - 1] = '\n';
	(*line)[gnl->line_len] = '\0';
	return (*line);
}

char	*get_lines(t_gnl *gnl, size_t len, char **line)
{
	t_list	*tmp;

	if (create_line(gnl, line) == NULL)
		return (NULL);
	while (gnl->lst && gnl->lst->cnt[gnl->lst->ofst] != '\n'
		&& gnl->lst->cnt[gnl->lst->ofst])
	{
		(*line)[len++] = gnl->lst->cnt[gnl->lst->ofst++];
		if (!(gnl->lst->cnt[gnl->lst->ofst]))
		{
			tmp = gnl->lst;
			gnl->lst = gnl->lst->nx;
			free(tmp);
		}
	}
	if (gnl->lst && gnl->is_nl)
		gnl->lst->ofst++;
	return (*line);
}

char	*get_next_line(int fd)
{
	static t_gnl	gnl = {0, 0, 0, NULL};
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	gnl.fd = fd;
	gnl.is_nl = 0;
	gnl.line_len = 0;
	if (gnl_lstnew(&(gnl.lst)) == NULL)
		return (gnl_free(&gnl));
	if (!get_content(&gnl, gnl.lst, 0, 0))
		return (gnl_free(&gnl));
	if (get_lines(&gnl, 0, &line) == NULL)
		return (gnl_free(&gnl));
	return (line);
}
