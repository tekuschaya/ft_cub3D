/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 09:14:27 by odhazzar          #+#    #+#             */
/*   Updated: 2020/08/13 22:58:31 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_pixel_color(t_texture *texture, int x, int y, float line)
{
	int		index;
	char	*dst;

	x = x * texture->width / line;
	y = y * texture->height / line;
	if (x > texture->width)
		x = x % texture->width;
	index = (x + y * texture->width) * 4;
	dst = texture->data + index;
	return (*(unsigned int*)dst);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
