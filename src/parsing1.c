/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 11:25:53 by odhazzar          #+#    #+#             */
/*   Updated: 2020/08/15 08:45:56 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			parse_resolution(t_vars *vars, char *s)
{
	if (vars->win_w == -1 && vars->win_h == -1)
	{
		s++;
		while (*s == ' ')
			s++;
		vars->win_w = (*s > 47 && *s < 58) ? 0 : -5;
		while (*s > 47 && *s < 58)
			vars->win_w = vars->win_w * 10 + *s++ - '0';
		while (*s == ' ')
			s++;
		vars->win_h = (*s > 47 && *s < 58) ? 0 : -5;
		while (*s > 47 && *s < 58)
			vars->win_h = vars->win_h * 10 + *s++ - '0';
		if (*s != '\0')
			return (0);
		vars->win_w = (vars->win_w > 1400) ? 1440 : vars->win_w;
		vars->win_h = (vars->win_h > 860) ? 860 : vars->win_h;
		return (1);
	}
	return (0);
}

static char	**ft_realloc(char **map, int i)
{
	int		j;
	char	**new;

	j = 0;
	new = map;
	map = (char**)malloc(sizeof(char*) * (i + 1));
	while (j < i)
	{
		map[j] = new[j];
		j++;
	}
	free(new);
	return (map);
}

int			parse_map(t_vars *vars, char *line, int fd)
{
	int i;

	i = 0;
	vars->map_w = 0;
	vars->map_h = 0;
	vars->map = (char**)malloc(sizeof(char*) * (i + 1));
	vars->map[i] = ft_strdup(line);
	i++;
	while (get_next_line(fd, &line) > 0)
	{
		vars->map = ft_realloc(vars->map, i);
		vars->map[i] = ft_strdup(line);
		if (ft_strlen(line) > vars->map_w)
			vars->map_w = ft_strlen(line);
		free(line);
		i++;
	}
	vars->map = ft_realloc(vars->map, i);
	vars->map[i] = ft_strdup(line);
	if (ft_strlen(line) > vars->map_w)
		vars->map_w = ft_strlen(line);
	free(line);
	vars->map_h = i + 1;
	return (0);
}
