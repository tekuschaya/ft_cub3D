/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 11:22:17 by odhazzar          #+#    #+#             */
/*   Updated: 2020/08/14 22:37:34 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int			parse_rgb(char *s, int r, int g, int b)
{
	r = (*s > 47 && *s < 58) ? 0 : -1;
	while (*s > 47 && *s < 58)
		r = r * 10 + *s++ - '0';
	while (*s == ' ' || *s == ',')
		s++;
	g = (*s > 47 && *s < 58) ? 0 : -1;
	while (*s > 47 && *s < 58)
		g = g * 10 + *s++ - '0';
	while (*s == ' ' || *s == ',')
		s++;
	b = (*s > 47 && *s < 58) ? 0 : -1;
	while (*s > 47 && *s < 58)
		b = b * 10 + *s++ - '0';
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255 || *s != '\0')
		return (-5);
	return (r << 16 | g << 8 | b);
}

static int			parse_color(t_vars *vars, char *s)
{
	char	c;
	int		r;
	int		g;
	int		b;

	r = -1;
	g = -1;
	b = -1;
	c = s[0];
	s++;
	while (*s == ' ')
		s++;
	if (c == 'F' && vars->floor == -1)
		vars->floor = parse_rgb(s, r, g, b);
	else if (c == 'C' && vars->ceiling == -1)
		vars->ceiling = parse_rgb(s, r, g, b);
	else
		return (0);
	return (1);
}

static t_texture	*load_texture(void *mlx_ptr, char *filename)
{
	t_texture	*res;
	int			config[3];

	if (!(res = malloc(sizeof(t_texture))))
		return (0);
	res->ptr = mlx_xpm_file_to_image(mlx_ptr, filename,
			&(res->width), &(res->height));
	if (!res->ptr)
		return (res);
	res->data = mlx_get_data_addr(res->ptr,
			&config[0], &config[1], &config[2]);
	res->x = 0;
	res->y = 0;
	return (res);
}

static int			parse_texture(t_vars *vars, char *s)
{
	char c1;
	char c2;

	if (ft_strlen(s) > 1)
	{
		c1 = s[0];
		c2 = s[1];
		while ((*s > 64 && *s < 91) || *s == ' ')
			s++;
		if (c1 == 'N' && c2 == 'O' && !(vars->north))
			vars->north = load_texture(vars->mlx, s);
		else if (c1 == 'S' && c2 == 'O' && !(vars->south))
			vars->south = load_texture(vars->mlx, s);
		else if (c1 == 'W' && c2 == 'E' && !(vars->west))
			vars->west = load_texture(vars->mlx, s);
		else if (c1 == 'E' && c2 == 'A' && !(vars->east))
			vars->east = load_texture(vars->mlx, s);
		else if (c1 == 'S' && c2 == ' ' && !(vars->sprite))
			vars->sprite = load_texture(vars->mlx, s);
		else
			return (0);
		return (1);
	}
	return (0);
}

int					parsing(t_vars *vars, int fd, int n)
{
	char	*line;

	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == 'R')
			n = n * parse_resolution(vars, line);
		else if (line[0] == 'F' || line[0] == 'C')
			n = n * parse_color(vars, line);
		else if (line[0] == 'S' || line[0] == 'N' ||
		line[0] == 'W' || line[0] == 'E')
			n = n * parse_texture(vars, line);
		else if (line[0] == '1' || line[0] == ' ' ||
		line[0] == '2' || line[0] == '0')
		{
			parse_map(vars, line, fd);
			break ;
		}
		else if (line[0] != '\0')
			n = 0;
		free(line);
		if (!n)
			return (0);
	}
	free(line);
	return (n);
}
