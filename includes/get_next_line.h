/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 10:32:37 by odhazzar          #+#    #+#             */
/*   Updated: 2020/08/13 19:32:47 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 1

# include <unistd.h>
# include <stdlib.h>

typedef struct		s_list
{
	int				fd;
	char			*remain;
	struct s_list	*next;
}					t_list;

int					get_next_line(int fd, char **line);
void				ft_free_list(int fd, t_list **lst);
int					ft_strlen(const char *str);
char				*ft_strchr(const char *str, int c);
char				*ft_strdup(const char *str);
char				*ft_substr(char const *s, unsigned int start, size_t len);

#endif
