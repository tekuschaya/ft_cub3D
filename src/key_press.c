/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 10:47:33 by odhazzar          #+#    #+#             */
/*   Updated: 2020/08/15 08:46:36 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	update_game(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img.img);
	vars->img.img = mlx_new_image(vars->mlx, vars->win_w, vars->win_h);
	vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bits_per_pixel,
	&vars->img.line_length, &vars->img.endian);
	vars->south->x = 0;
	vars->north->x = 0;
	vars->east->x = 0;
	vars->west->x = 0;
	vars->sprite->x = 0;
	if (vars->angle > 2 * M_PI)
		vars->angle = vars->angle - 2 * M_PI;
	if (vars->angle < 0)
		vars->angle = 2 * M_PI + vars->angle;
	raycast(vars, 0, 0.1);
	raycast_sprite(vars, 0, 0.1, 0);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	print_sprite_count(vars, vars->sprite->y);
	return (0);
}

static void	check_borders(t_vars *vars, float x, float y)
{
	if (y <= vars->map_h && y >= 0 && x <= vars->map_w && x >= 0 &&
	(vars->map[(int)y][(int)x] != '1' &&
	vars->map[(int)(y + 0.2)][(int)x] != '1' &&
	vars->map[(int)y][(int)(x + 0.2)] != '1' &&
	vars->map[(int)(y + 0.2)][(int)(x + 0.2)] != '1' &&
	vars->map[(int)(y - 0.2)][(int)x] != '1' &&
	vars->map[(int)y][(int)(x - 0.2)] != '1' &&
	vars->map[(int)(y - 0.2)][(int)(x - 0.2)] != '1'))
	{
		vars->player_x = x;
		vars->player_y = y;
	}
}

int			key_press(int key, t_vars *vars)
{
	if (key == 53)
		stop_game(vars);
	if (key == 13 || key == 126)
		check_borders(vars, vars->player_x + cos(vars->angle) * 0.25,
		vars->player_y + sin(vars->angle) * 0.25);
	if (key == 1 || key == 125)
		check_borders(vars, vars->player_x - cos(vars->angle) * 0.25,
		vars->player_y - sin(vars->angle) * 0.25);
	if (key == 0)
		check_borders(vars, vars->player_x - cos(vars->angle + M_PI_2) * 0.25,
		vars->player_y - sin(vars->angle + M_PI_2) * 0.25);
	if (key == 2)
		check_borders(vars, vars->player_x - cos(vars->angle - M_PI_2) * 0.25,
		vars->player_y - sin(vars->angle - M_PI_2) * 0.25);
	if (key == 124)
		vars->angle += M_PI / 10;
	if (key == 123)
		vars->angle -= M_PI / 10;
	update_game(vars);
	return (0);
}
