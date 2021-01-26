/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 09:21:51 by odhazzar          #+#    #+#             */
/*   Updated: 2020/08/15 10:37:54 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	surround_wall(char **map, int x, int y, int n)
{
	map[x][y] = '5';
	if (map[x - 1][y] == ' ' || map[x][y - 1] == ' ' || map[x - 1][y - 1] == ' '
	|| map[x + 1][y] == ' ' || map[x][y + 1] == ' ' || map[x + 1][y + 1] == ' '
	|| map[x + 1][y - 1] == ' ' || map[x - 1][y + 1] == ' ')
		n = 0;
	if (map[x - 1][y] == '0' || map[x - 1][y] == '2')
		n = n * surround_wall(map, x - 1, y, n);
	if (map[x][y - 1] == '0' || map[x][y - 1] == '2')
		n = n * surround_wall(map, x, y - 1, n);
	if (map[x - 1][y - 1] == '0' || map[x - 1][y - 1] == '2')
		n = n * surround_wall(map, x - 1, y - 1, n);
	if (map[x + 1][y] == '0' || map[x + 1][y] == '2')
		n = n * surround_wall(map, x + 1, y, n);
	if (map[x][y + 1] == '0' || map[x][y + 1] == '2')
		n = n * surround_wall(map, x, y + 1, n);
	if (map[x + 1][y + 1] == '0' || map[x + 1][y + 1] == '2')
		n = n * surround_wall(map, x + 1, y + 1, n);
	if (map[x + 1][y - 1] == '0' || map[x + 1][y - 1] == '2')
		n = n * surround_wall(map, x + 1, y - 1, n);
	if (map[x - 1][y + 1] == '0' || map[x - 1][y + 1] == '2')
		n = n * surround_wall(map, x - 1, y + 1, n);
	return (n);
}

static int	fill_new_map(char **new_map, t_vars *vars, int i, int j)
{
	char	*symb;

	symb = " 012WSNE";
	if (i == 0 || i == (vars->map_h + 1) || vars->map[i - 1][j] == '\0')
	{
		while (j < (vars->map_w + 2))
			new_map[i][j++] = ' ';
		new_map[i][j] = '\0';
	}
	else
	{
		new_map[i][0] = ' ';
		while (vars->map[i - 1][j])
		{
			if (!(ft_strchr(symb, vars->map[i - 1][j])))
				return (0);
			new_map[i][j + 1] = vars->map[i - 1][j];
			if (new_map[i][j++ + 1] == '2')
				vars->sprite->y++;
		}
		while (++j < vars->map_w + 2)
			new_map[i][j] = ' ';
		new_map[i][j] = '\0';
	}
	return (1);
}

static int	check_map(t_vars *vars, int i)
{
	char	**new_map;

	if (!(new_map = (char**)malloc(sizeof(char*) * (vars->map_h + 2))))
		return (0);
	while (i < vars->map_h + 2)
	{
		if (!(new_map[i] = (char*)malloc(sizeof(char) * (vars->map_w + 3))))
			return (0);
		if (!(fill_new_map(new_map, vars, i, 0)))
		{
			clear_map(new_map, i + 1);
			return (0);
		}
		i++;
	}
	if (!(surround_wall(new_map, vars->player_y, vars->player_x, 1)))
	{
		clear_map(new_map, vars->map_h + 2);
		return (0);
	}
	clear_map(new_map, vars->map_h + 2);
	return (1);
}

static int	check_coordinats(char **map, t_vars *vars, int i, int j)
{
	int flag;

	flag = 0;
	while (i < vars->map_h)
	{
		while (map[i][j])
		{
			if ((map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' ||
			map[i][j] == 'W') && flag == 0)
			{
				if (i == 0 || i == vars->map_h - 1 || j == 0 ||
				j == ft_strlen(map[i]) - 1)
					return (0);
				check_orientation(vars, map[i][j], i, j);
				flag = 1;
			}
			else if ((map[i][j] == 'N' || map[i][j] == 'S' ||
			map[i][j] == 'E' || map[i][j] == 'W') && flag == 1)
				return (0);
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

int			error(t_vars *vars)
{
	if (!vars->map)
		write(1, "Error\nMap is empty\n", 20);
	else if (!(check_coordinats(vars->map, vars, 0, 0)) ||
	vars->player_x < 0 || vars->player_y < 0)
		write(1, "Error\nIncorrect coordinats\n", 28);
	else if (!(vars->north->ptr) || !(vars->south->ptr) || !(vars->west->ptr) ||
	!(vars->east->ptr) || !(vars->sprite->ptr))
		write(1, "Error\nTexture doesn't exist\n", 29);
	else if (vars->ceiling < 0 || vars->floor < 0)
		write(1, "Error\nIncorrect color\n", 23);
	else if (vars->win_w < 0 || vars->win_h < 0)
		write(1, "Error\nIncorrect resolution\n", 28);
	else if (!(check_map(vars, 0)))
		write(1, "Error\nIncorrect map\n", 21);
	else
		return (1);
	return (0);
}
