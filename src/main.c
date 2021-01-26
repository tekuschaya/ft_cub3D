/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 11:15:11 by odhazzar          #+#    #+#             */
/*   Updated: 2020/08/15 08:31:38 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_vars(t_vars *vars)
{
	vars->screenshot = 0;
	vars->player_x = -1;
	vars->player_y = -1;
	vars->angle = 0;
	vars->floor = -1;
	vars->ceiling = -1;
	vars->win_h = -1;
	vars->win_w = -1;
	vars->north = NULL;
	vars->south = NULL;
	vars->west = NULL;
	vars->east = NULL;
	vars->sprite = NULL;
	vars->map = NULL;
}

int			main(int argc, char **argv)
{
	t_vars	vars;
	int		fd;

	vars.mlx = mlx_init();
	init_vars(&vars);
	if (argc < 2 || argc > 3)
		write(1, "Error\nIncorrect number of arguments\n", 37);
	else if (!(check_file_format(argv[1])) ||
	(fd = open(argv[1], O_RDONLY)) < 0)
		write(1, "Error\nInvalid map name\n", 24);
	else if (argc == 3 && (ft_strcmp(argv[2], "--save")))
	{
		vars.screenshot = 1;
		start_game(vars, fd);
	}
	else if (argc == 3)
		write(1, "Error\nThe second argument is invalid\n", 38);
	else
		start_game(vars, fd);
	return (0);
}
