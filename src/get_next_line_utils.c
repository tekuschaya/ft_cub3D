/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 10:29:31 by odhazzar          #+#    #+#             */
/*   Updated: 2020/08/13 20:36:09 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_free_list(int fd, t_list **lst)
{
	t_list	*first;
	t_list	*tmp;

	if ((*lst)->fd == fd)
	{
		tmp = *lst;
		*lst = (*lst)->next;
	}
	else
	{
		first = *lst;
		while ((*lst)->next->fd != fd)
			*lst = (*lst)->next;
		tmp = (*lst)->next;
		(*lst)->next = tmp->next;
		*lst = first;
	}
	free(tmp->remain);
	free(tmp);
}

int		ft_strlen(const char *str)
{
	int i;

	i = 0;
	if (str)
		while (str[i] != '\0')
			i++;
	return (i);
}

char	*ft_strchr(const char *str, int c)
{
	char *ptr;

	ptr = (char*)str;
	while (*ptr)
	{
		if (*ptr == (char)c)
			return (ptr);
		ptr++;
	}
	if ((char)c == '\0')
		return (ptr);
	return (ptr = NULL);
}

char	*ft_strdup(const char *str)
{
	int		i;
	char	*str1;

	i = 0;
	str1 = (char*)malloc(ft_strlen(str) + 1);
	if (str1)
	{
		while (str[i])
		{
			str1[i] = str[i];
			i++;
		}
		str1[i] = '\0';
		return (str1);
	}
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	int		size;
	int		i;

	i = 0;
	if (!s)
		return (ft_strdup(""));
	size = (int)ft_strlen(s) - (int)start;
	if (size <= 0)
		return (ft_strdup(""));
	if ((unsigned int)size < len)
		len = (unsigned int)size;
	str = (char*)malloc(len + 1);
	if (str)
	{
		while (len > 0)
		{
			str[i++] = s[start++];
			len--;
		}
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}
