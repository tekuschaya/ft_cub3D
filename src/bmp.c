/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 14:02:02 by odhazzar          #+#    #+#             */
/*   Updated: 2020/08/15 09:20:51 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	int_to_char(int n, unsigned char *src)
{
	src[0] = (unsigned char)(n);
	src[1] = (unsigned char)(n >> 8);
	src[2] = (unsigned char)(n >> 16);
	src[3] = (unsigned char)(n >> 24);
}

static int	get_pixel(t_vars *vars, int x, int y)
{
	int	ptr;

	ptr = *(int*)(vars->img.addr + 4 * vars->win_w *
	(vars->win_h - 1 - y) + 4 * x);
	return ((ptr & 0xFF0000) | (ptr & 0x00FF00) | (ptr & 0x0000FF));
}

static void	bmp_header(t_vars *vars, int fd, int filesize)
{
	int				i;
	unsigned char	data[54];

	i = 0;
	while (i < 54)
		data[i++] = 0;
	data[0] = (unsigned char)('B');
	data[1] = (unsigned char)('M');
	int_to_char(filesize, data + 2);
	data[10] = (unsigned char)(54);
	data[14] = (unsigned char)(40);
	int_to_char(vars->win_w, data + 18);
	int_to_char(vars->win_h, data + 22);
	data[26] = (unsigned char)(1);
	data[28] = (unsigned char)(24);
	write(fd, data, 54);
}

static void	bmp_pixels(t_vars *vars, int fd)
{
	int	i;
	int j;
	int	color;

	i = 0;
	while (i < vars->win_h)
	{
		while (j < vars->win_w)
		{
			color = get_pixel(vars, j++, i);
			write(fd, &color, 3);
		}
		i++;
		j = 0;
	}
}

int			screenshot(t_vars *vars)
{
	int			fd;
	int			filesize;

	filesize = vars->win_w * vars->win_h * 4 + 54;
	if ((fd = open("screenshot.bmp", O_WRONLY | O_CREAT | O_TRUNC, 0666)) < 0)
		return (0);
	bmp_header(vars, fd, filesize);
	bmp_pixels(vars, fd);
	close(fd);
	return (1);
}
