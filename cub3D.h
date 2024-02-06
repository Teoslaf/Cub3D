/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaneski <ttaneski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:18:49 by cdurro            #+#    #+#             */
/*   Updated: 2024/02/06 15:42:19 by ttaneski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line.h"
# include "libft/libft.h"
# include "mlx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define F 1
# define C 2
# define NUM 3
# define COMMA 4
# define WIDTH 1280
# define HEIGHT 1024
# define ESC 65307

typedef struct s_ray
{
	double			camera_x;
	double			dir_x;
	double			dir_y;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			wall_dist;
	double			wall_x;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
}					t_ray;

typedef struct s_texture
{
	int				*floor;
	int				*ceiling;
	int				size;
	int				index;
	int				x;
	int				y;
	unsigned int	hex_floor;
	unsigned int	hex_ceiling;
	double			step;
	double			pos;
}					t_texture;

typedef struct s_player
{
	int				rotate;
	int				move_x;
	int				move_y;

	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	char			direction;
}					t_player;

typedef struct s_image
{
	void			*img;
	char			*address;
	int				bitxpixel;
	int				line_len;
	int				endian;
}					t_image;

typedef struct s_vars
{
	void			*mlx;
	void			*win;
}					t_vars;

typedef struct s_map
{
	char			player_char;
	int				player_x;
	int				player_y;
	int				height;
	int				width;
	int				north_set;
	int				south_set;
	int				west_set;
	int				east_set;
	int				floor_set;
	int				ceiling_set;
	int				map_set;
	int				rows_set;
	int				map_start;
	int				time;
	int				old_time;
	int				**textures;
	char			**floor;
	char			**ceiling;
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			**map;
	t_player		player;
	t_texture		texture;
	t_image			image;
	t_vars			vars;
	t_ray			ray;
}					t_map;

int					read_map(char *map_file, t_map *map);
int					get_color(char *line, t_map *map);
int					get_texture(char *line, t_map *map);
int					is_valid_path(t_map *map);
int					path(t_map *temp, int y, int x);
void				copy_game(t_map *source, t_map *destination);
void				check_cords(t_map *map);
int					get_pos_by_char(t_map *map, char c, char search_char);
int					check_size(t_map *map);
int					check_player(t_map *map);
int					empty_map(char *map_file);
int					check_file_extension(char *file);
int					check_texture_extension(char *file);

void				free_map(t_map *map);
void				print_map(t_map map);
void				free_map_double(t_map *map);

// HOOK FUNCTIONS
int					handle_key_down(int key, t_map *map);
int					close_window(t_map *map);
int					draw_map(t_map *map);

#endif