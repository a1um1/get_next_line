/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 09:56:34 by codespace         #+#    #+#             */
/*   Updated: 2023/11/24 15:47:15 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*free_all(t_gnl *gnl)
{
	t_list	*tmp;

	while (gnl->list != NULL)
	{
		tmp = gnl->list;
		gnl->list = gnl->list->nx;
		free(tmp);
	}
	return (NULL);
}

t_list	*ft_lstnew(void)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (list == NULL)
		return (NULL);
	list->nx = NULL;
	list->cnt[0] = '\0';
	return (list);
}

bool	get_content(t_gnl *gnl)
{
	t_list	*tmp;
	int		rd_bytes;

	if (gnl->list == NULL)
		gnl->list = ft_lstnew();
	if (gnl->list == NULL)
		return (false);
	tmp = gnl->list;
	if (strchr(tmp->cnt, '\n') != NULL)
		return (true);
	while (tmp != NULL)
	{
		if (tmp->cnt[0] == '\0')
		{
			rd_bytes = read(gnl->fd, tmp->cnt, BUFFER_SIZE);
			if (rd_bytes < 1)
				return (!(rd_bytes < 0));
			tmp->cnt[rd_bytes] = '\0';
			if (strchr(tmp->cnt, '\n') != NULL)
				return (true);
		}
		tmp->nx = ft_lstnew();
		if (tmp->nx == NULL)
			return (false);
		tmp = tmp->nx;
	}
	return (true);
}

char	*get_lines(t_gnl *gnl)
{
	char	*line;
	t_list	*tmp;
	size_t	i;
	size_t	len;

	tmp = gnl->list;
	if (tmp->cnt[0] == '\0')
		return (NULL);
	len = 0;
	i = 0;
	while (tmp != NULL && !(tmp->cnt[i] == '\0' || tmp->cnt[i] == '\n'))
	{
		i++;
		if (tmp->cnt[i] == '\0' && tmp->nx != NULL)
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
	len = 0;
	i = 0;
	while (gnl->list != NULL && !(gnl->list->cnt[i] == '\0'
			|| gnl->list->cnt[i] == '\n'))
	{
		line[len++] = gnl->list->cnt[i++];
		if (gnl->list->cnt[i] == '\0')
		{
			tmp = gnl->list;
			gnl->list = gnl->list->nx;
			free(tmp);
			i = 0;
		}
	}
	len = i + 1;
	if (gnl->list->cnt[i] == '\n')
	{
		i = 0;
		while (gnl->list->cnt[len + i] != '\0')
		{
			gnl->list->cnt[i] = gnl->list->cnt[len + i];
			i++;
		}
		gnl->list->cnt[i] = '\0';
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static t_gnl	gnl;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	gnl.fd = fd;
	if (!get_content(&gnl))
		return (free_all(&gnl));
	// print_linked_list(gnl.list);
	line = get_lines(&gnl);
	if (line == NULL)
		return (free_all(&gnl));
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("multiple_line_with_nl", O_RDONLY);
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	return (0);
// }
