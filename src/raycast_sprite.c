/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_sprite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 12:37:17 by odhazzar          #+#    #+#             */
/*   Updated: 2020/08/14 16:02:13 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		print_sprite_count(t_vars *vars, int count)
{
	char	*res;
	int		len;
	int		i;

	i = count;
	len = 1;
	while (i /= 10)
		len++;
	res = (char*)malloc(len + 1);
	if (res)
	{
		res[len--] = '\0';
		while (len >= 0)
		{
			res[len--] = count % 10 + '0';
			count /= 10;
		}
		mlx_string_put(vars->mlx, vars->win, 10, 20, 0, "LEFT TO CATCH: ");
		mlx_string_put(vars->mlx, vars->win, 10, 30, 0, res);
		free(res);
	}
}

static void	draw_sprite(t_vars *vars, int i, int j, float line)
{
	int	top;
	int	k;
	int	color1;
	int	color2;

	k = 0;
	color1 = get_pixel_color(vars->sprite, 0, 0, line);
	top = (vars->win_h / 2 - line / 8);
	j = top;
	while (k < line)
	{
		while (j < (vars->win_h / 2 + line / 2))
		{
			color2 = get_pixel_color(vars->sprite, k, j - top, line);
			if (color2 != color1)
				my_mlx_pixel_put(&vars->img, i + k, j, color2);
			j++;
		}
		j = top;
		k++;
	}
}

static void	check_draw_sprite(t_vars *vars, int i, int *j, float *t_sum)
{
	float distance;
	float line;

	if (*j != 0)
	{
		distance = *t_sum / *j;
		line = vars->win_h / distance;
		i = ((i - *j / 2 - line / 2) > 0) ? (i - *j / 2 - line / 2) : 0;
		if ((int)distance == 0)
		{
			vars->map[vars->temp_y][vars->temp_x] = '0';
			vars->sprite->y--;
			*j = 0;
		}
		if (*j > vars->win_w / distance && (i + line < vars->win_w))
			draw_sprite(vars, i, *j, line);
		*j = 0;
		*t_sum = 0;
	}
}

static int	count_sprite_width(t_vars *vars, float t, float angle)
{
	float x;
	float y;

	x = vars->player_x + t * cos(angle) * 0.4;
	y = vars->player_y + t * sin(angle) * 0.4;
	if (vars->map[(int)y][(int)x] == '1' || vars->sprite->x == vars->win_w - 1)
		return (1);
	if (vars->map[(int)y][(int)x] == '2')
	{
		if (abs(vars->temp_x - (int)x) >= 1 || abs(vars->temp_y - (int)y) >= 1)
		{
			vars->temp_x = (int)x;
			vars->temp_y = (int)y;
			return (2);
		}
		return (3);
	}
	return (0);
}

void		raycast_sprite(t_vars *vars, int j, float t, float t_sum)
{
	float	angle;
	int		res;

	while (vars->sprite->x < vars->win_w)
	{
		angle = check_angle(vars, vars->sprite->x);
		while (t < (vars->map_w + vars->map_h) * 2)
		{
			if ((res = count_sprite_width(vars, t, angle)) > 0)
			{
				if (res < 3)
					check_draw_sprite(vars, vars->sprite->x, &j, &t_sum);
				if (res > 1)
				{
					t_sum += t;
					j++;
				}
				break ;
			}
			t += 0.1;
		}
		t = 0.1;
		vars->sprite->x++;
	}
}
