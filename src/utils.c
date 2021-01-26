/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 17:00:49 by odhazzar          #+#    #+#             */
/*   Updated: 2020/08/13 21:19:15 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (0);
		s1++;
		s2++;
	}
	if (*s1 != *s2)
		return (0);
	return (1);
}

void	clear_map(char **map, int height)
{
	int i;

	i = 0;
	while (i < height)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

float	check_angle(t_vars *vars, int i)
{
	float angle;
	float fov;

	fov = M_PI / 3;
	angle = vars->angle - fov / 2 + fov * i / vars->win_w;
	if (angle > 2 * M_PI)
		angle = angle - 2 * M_PI;
	if (angle < 0)
		angle = 2 * M_PI + angle;
	return (angle);
}

int		check_file_format(char *filename)
{
	int len;

	len = ft_strlen(filename);
	if (len >= 4)
	{
		filename = filename + len - 4;
		if (ft_strcmp(filename, ".cub"))
			return (1);
	}
	return (0);
}

void	check_orientation(t_vars *vars, char c, int i, int j)
{
	vars->player_x = j + 0.5;
	vars->player_y = i + 0.5;
	if (c == 'S')
		vars->angle = M_PI_2;
	if (c == 'W')
		vars->angle = M_PI;
	if (c == 'N')
		vars->angle = M_PI + M_PI_2;
}
