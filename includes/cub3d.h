/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 15:46:45 by odhazzar          #+#    #+#             */
/*   Updated: 2020/08/15 10:42:40 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include "get_next_line.h"
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>

typedef struct	s_data {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct	s_texture
{
	int			width;
	int			height;
	char		*filename;
	void		*ptr;
	char		*data;
	int			x;
	int			y;
}				t_texture;

typedef struct	s_vars {
	void		*mlx;
	void		*win;
	float		angle;
	float		player_x;
	float		player_y;
	int			temp_x;
	int			temp_y;
	char		**map;
	int			map_h;
	int			map_w;
	int			win_h;
	int			win_w;
	int			floor;
	int			ceiling;
	int			screenshot;
	t_data		img;
	t_texture	*north;
	t_texture	*south;
	t_texture	*west;
	t_texture	*east;
	t_texture	*sprite;
	t_texture	*tmp;
}				t_vars;

int				parsing(t_vars *vars, int fd, int n);
int				parse_map(t_vars *vars, char *line, int fd);
int				parse_resolution(t_vars *vars, char *s);
int				error(t_vars *vars);
void			start_game(t_vars vars, int fd);
void			stop_game(t_vars *vars);
void			raycast(t_vars *vars, int i, float t);
void			raycast_sprite(t_vars *vars, int j, float t, float t_sum);
void			print_sprite_count(t_vars *vars, int count);
int				get_pixel_color(t_texture *texture, int x, int y, float line);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
int				screenshot(t_vars *game);
int				check_file_format(char *filename);
void			clear_map(char **map, int height);
int				key_press(int key, t_vars *vars);
float			check_angle(t_vars *vars, int i);
int				ft_strcmp(char *s1, char *s2);
void			check_orientation(t_vars *vars, char c, int i, int j);

#endif
