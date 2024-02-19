/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaneski <ttaneski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:18:49 by cdurro            #+#    #+#             */
/*   Updated: 2024/02/19 16:59:48 by ttaneski         ###   ########.fr       */
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
# define WIDTH 1920
# define HEIGHT 1080
# define ESC 65307
# define A 97
# define S 115
# define W 119
# define D 100
# define MINIMAP 109
# define LEFT_ARROW 65361
# define UP_ARROW 65362
# define RIGHT_ARROW 65363
# define DOWN_ARROW 65364
# define PI 3.1415926535
# define SQUARE 25
# define PLAYER 5

enum				e_texture
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
};

typedef struct s_ray
{
	double			xo;
	double			yo;
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
	int				fov;
	int				side;

	double			move_x;
	double			move_y;

	double			angle;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			old_dir_x;
	double			old_dir_y;
	double			step_x;
	double			step_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	double			plane_x;
	double			plane_y;
	double			old_plane_x;
	double			old_plane_y;
	double			ray_dir_x;
	double			ray_dir_y;

	char			direction;
}					t_player;

typedef struct s_mouse
{
	int				pressed;
	double			curr_x;
	double			curr_y;
	double			prev_x;
	double			prev_y;
}					t_mouse;

typedef struct s_image
{
	void			*img;
	char			*address;
	int				bitxpixel;
	int				line_len;
	int				endian;
	int				width;
	int				height;
	int				xoff;
	int				yoff;

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
	int				player_xpos;
	int				player_ypos;
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
	int				minimap;
	char			**floor;
	char			**ceiling;
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			**map;
	double			angle;
	t_player		player;
	t_image			image;
	t_image			**textures;
	t_vars			vars;
	t_ray			ray;
	t_mouse			mouse;
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
int					check_texture_extension(char *file, char **format);

void				free_map(t_map *map);
void				print_map(t_map map);
void				free_map_double(t_map *map);

// HOOK FUNCTIONS
int					handle_key_down(int key, t_map *map);
int					mouse_press(int button, int x, int y, t_map *map);
int					mouse_release(int button, int x, int y, t_map *map);
int					mouse_move(int x, int y, t_map *map);
int					close_window(t_map *map);

int					get_map_line_width(char *map_file, t_map *map);
int					floor_ceiling_check(char *line, int j, int row, t_map *map);
int					texture_check(char *line, int j, int row, t_map *map);
int					map_line_check(char *line, int row, t_map *map);
void				fill_nums(int *i, int *j, char *line, t_map *map);
void				fill(char c, int *j, int **format, t_map *map);
void				free_floor_ceiling(int j, char c, t_map *map);
int					color_format_check(int j, int *format);
int					fill_functions(char c, int *j, int **format, t_map *map);

int					is_map_line(char *line);
int					get_map_height(char *map_file, t_map *map);

void				replace_tab_to_space(char **map);
int					handle_key_down(int key, t_map *map);
void				minimap(t_map *map);
void				draw_square(t_map *map, int xpos, int ypos);
void				my_pixel_put(t_image *image, int x, int y, int color);
void				draw_background(t_map *map);
int					create_rgb(char **color);
void				show_map(t_map *map);
int					read_map(char *map_file, t_map *map);

void				move_right(t_map *map, double step);
void				move_left(t_map *map, double step);
void				move_backward(t_map *map, double step);
void				move_forward(t_map *map, double step);
void				handle_rotation(int key, t_map *map);
void				handle_movement(int key, t_map *map);
int					mouse_move(int x, int y, t_map *map);
void				redraw_map(t_map *map);
int					rotate(t_map *map, double angle);

#endif