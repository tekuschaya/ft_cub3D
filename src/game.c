/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 20:46:10 by odhazzar          #+#    #+#             */
/*   Updated: 2020/08/15 08:29:16 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	destroy_texture(void *mlx_ptr, t_texture *texture)
{
	if (mlx_ptr && texture && texture->ptr)
		mlx_destroy_image(mlx_ptr, texture->ptr);
	free(texture);
}

static void	destroy_game(t_vars *vars)
{
	destroy_texture(vars->mlx, vars->north);
	destroy_texture(vars->mlx, vars->south);
	destroy_texture(vars->mlx, vars->west);
	destroy_texture(vars->mlx, vars->east);
	destroy_texture(vars->mlx, vars->sprite);
	if (vars->map)
		clear_map(vars->map, vars->map_h);
	exit(EXIT_FAILURE);
}

void		stop_game(t_vars *vars)
{
	destroy_texture(vars->mlx, vars->north);
	destroy_texture(vars->mlx, vars->south);
	destroy_texture(vars->mlx, vars->west);
	destroy_texture(vars->mlx, vars->east);
	destroy_texture(vars->mlx, vars->sprite);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_image(vars->mlx, vars->img.img);
	clear_map(vars->map, vars->map_h);
	exit(EXIT_SUCCESS);
}

static int	ft_exit(t_vars *vars)
{
	stop_game(vars);
	return (0);
}

void		start_game(t_vars vars, int fd)
{
	if (!(parsing(&vars, fd, 1)))
	{
		write(1, "Error\nInvalid or double identifier\n", 36);
		close(fd);
		destroy_game(&vars);
	}
	if (!(error(&vars)))
		destroy_game(&vars);
	vars.win = mlx_new_window(vars.mlx, vars.win_w, vars.win_h, "odhazzar");
	vars.img.img = mlx_new_image(vars.mlx, vars.win_w, vars.win_h);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel,
	&vars.img.line_length, &vars.img.endian);
	raycast(&vars, 0, 0.1);
	raycast_sprite(&vars, 0, 0.1, 0);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);
	print_sprite_count(&vars, vars.sprite->y);
	if (vars.screenshot)
	{
		screenshot(&vars);
		stop_game(&vars);
	}
	mlx_hook(vars.win, 17, 1L << 17, ft_exit, &vars);
	mlx_hook(vars.win, 2, 1L << 0, key_press, &vars);
	mlx_loop(vars.mlx);
}
