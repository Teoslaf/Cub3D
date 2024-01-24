/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaneski <ttaneski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:18:49 by cdurro            #+#    #+#             */
/*   Updated: 2024/01/24 16:06:15 by ttaneski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line.h"
# include "libft/libft.h"
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

typedef struct s_map
{
	char	player_char;
	int	player_x;
	int	player_y;
	int		height;
	int		width;
	int		north_set;
	int		south_set;
	int		west_set;
	int		east_set;
	int		floor_set;
	int		ceiling_set;
	int		map_set;
	int		rows_set;
	int		map_end;
	char	**floor;
	char	**ceiling;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	**map;
}			t_map;

int			read_map(char *map_file, t_map *map);
int			get_color(char *line, t_map *map);
int			get_texture(char *line, t_map *map);
int			is_valid_path(t_map *map);
int			path(t_map *temp, int y, int x);
void		copy_game(t_map *source, t_map *destination);
void		check_cords(t_map *map);
int			get_pos_by_char(t_map *map, char c, char search_char);
int			checkSize(t_map *map);
int			check_player(t_map *map);
int			empty_map(char *map_file);
void		check_file_extension(char *file);

void		free_map(t_map *map);
void		print_map(t_map map);

#endif