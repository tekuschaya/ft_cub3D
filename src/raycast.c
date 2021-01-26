/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 16:55:31 by odhazzar          #+#    #+#             */
/*   Updated: 2020/08/14 17:38:20 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_texture	*check_texture(t_vars *vars, float x, float y, float angle)
{
	float x_diff;
	float y_diff;

	x_diff = x - (int)x;
	y_diff = y - (int)y;
	if (x_diff > 0.999 || x_diff < 0.001)
		x_diff = 0;
	if (y_diff > 0.999 || y_diff < 0.001)
		y_diff = 0;
	if (x_diff == 0 && y_diff == 0)
		return (vars->tmp);
	else if (y_diff == 0 && angle <= M_PI)
		return (vars->north);
	else if (y_diff == 0 && angle >= M_PI)
		return (vars->south);
	else if (x_diff == 0 && angle >= M_PI / 2 && angle <= (M_PI + M_PI / 2))
		return (vars->east);
	else
		return (vars->west);
}

static void			draw_wall(t_vars *vars, float line, int i, int j)
{
	int	top;
	int	bottom;
	int	temp_j;
	int	color;

	temp_j = 0;
	top = (vars->win_h / 2 - line / 2);
	bottom = (vars->win_h / 2 + line / 2);
	if (line > vars->win_h)
	{
		top = 0;
		temp_j = (line - vars->win_h) / 2;
		bottom = vars->win_h;
	}
	while (j < top)
		my_mlx_pixel_put(&vars->img, i, j++, vars->ceiling);
	while (j < bottom)
	{
		color = get_pixel_color(vars->tmp, vars->tmp->x, temp_j++, line);
		my_mlx_pixel_put(&vars->img, i, j++, color);
	}
	while (j < vars->win_h)
		my_mlx_pixel_put(&vars->img, i, j++, vars->floor);
	vars->tmp->x++;
}

static void			check_border(t_vars *vars, int x, int y)
{
	if (abs(vars->temp_x - x) >= 1 || abs(vars->temp_y - y) >= 1)
	{
		vars->west->x = 0;
		vars->north->x = 0;
		vars->east->x = 0;
		vars->south->x = 0;
		vars->temp_x = x;
		vars->temp_y = y;
	}
}

void				raycast(t_vars *vars, int i, float t)
{
	float	x;
	float	y;
	float	angle;

	while (i < vars->win_w)
	{
		angle = check_angle(vars, i);
		while (t < (vars->map_w + vars->map_h) * 2)
		{
			x = vars->player_x + t * cos(angle) * 0.4;
			y = vars->player_y + t * sin(angle) * 0.4;
			if (vars->map[(int)y][(int)x] == '1')
			{
				check_border(vars, (int)x, (int)y);
				vars->tmp = check_texture(vars, x, y, angle);
				draw_wall(vars, vars->win_h /
				(t * cos(angle - vars->angle)), i, 0);
				break ;
			}
			t += 0.001;
		}
		t = 0.01;
		i++;
	}
}
