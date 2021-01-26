/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 10:17:44 by odhazzar          #+#    #+#             */
/*   Updated: 2020/08/13 19:35:21 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		*ft_fill_line(char *remain, char **line, int count)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!count && !remain)
	{
		*line = ft_strdup("");
		return (NULL);
	}
	while (remain[i] && remain[i] != '\n')
		i++;
	if (i < ft_strlen(remain))
	{
		*line = ft_substr(remain, 0, i);
		tmp = ft_substr(remain, i + 1, ft_strlen(remain));
		free(remain);
		remain = ft_strdup(tmp);
		free(tmp);
	}
	else if (count == 0)
	{
		*line = remain;
		remain = NULL;
	}
	return (remain);
}

static char		*ft_fill_remain(char *buf, char *remain)
{
	char	*tmp;
	char	*ptr;
	int		i;

	i = 0;
	if (remain)
	{
		if (!(tmp = (char*)malloc(ft_strlen(remain) + ft_strlen(buf) + 1)))
			return (NULL);
		ptr = (char*)tmp;
		while (remain[i])
			*ptr++ = remain[i++];
		i = 0;
		while (buf[i])
			*ptr++ = buf[i++];
		*ptr = '\0';
		free(remain);
		remain = ft_strdup(tmp);
		free(tmp);
	}
	else
		remain = ft_strdup(buf);
	return (remain);
}

static int		ft_get_line(int fd, char **line, char **remain)
{
	char	*buf;
	int		count;

	if (!(buf = (char*)malloc(sizeof(char) * BUFFER_SIZE + 1)))
		return (-1);
	while ((count = read(fd, buf, BUFFER_SIZE)))
	{
		if (count == -1)
		{
			free(buf);
			return (-1);
		}
		buf[count] = '\0';
		if (!(*remain = ft_fill_remain(buf, *remain)))
			return (-1);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(buf);
	if (!(*remain = ft_fill_line(*remain, line, count)))
		return (0);
	return (1);
}

static t_list	*ft_new_list(int fd)
{
	t_list	*new;

	if (!(new = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	new->fd = fd;
	new->remain = NULL;
	new->next = NULL;
	return (new);
}

int				get_next_line(int fd, char **line)
{
	static t_list	*head;
	t_list			*tmp;
	int				i;

	if (BUFFER_SIZE <= 0 || fd < 0 || !line)
		return (-1);
	if (head == NULL)
		head = ft_new_list(fd);
	if (!head)
		return (-1);
	tmp = head;
	while (tmp->fd != fd)
	{
		if (tmp->next == NULL)
			if (!(tmp->next = ft_new_list(fd)))
			{
				ft_free_list(fd, &head);
				return (-1);
			}
		tmp = tmp->next;
	}
	i = ft_get_line(tmp->fd, line, &tmp->remain);
	if (i <= 0)
		ft_free_list(fd, &head);
	return (i);
}
