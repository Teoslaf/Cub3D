/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaneski <ttaneski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:21:44 by cdurro            #+#    #+#             */
/*   Updated: 2024/01/23 12:17:33 by ttaneski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	is_map_line(char *line)
{
	if ((ft_strchr(line, '0') || ft_strchr(line, '1')) && !ft_strchr(line, 'F')
		&& !ft_strchr(line, 'C'))
		return (1);
	return (0);
}

static int	get_map_height(char *map_file)
{
	int		height;
	int		fd;
	char	*line;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
	{
		printf("Error opening the map\n");
		return (1);
	}
	height = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!is_map_line(line))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (height);
}

static int	get_map_line_width(char *map_file, t_map *map)
{
	int		row;
	int		fd;
	char	*line;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
	{
		printf("Error opening the map\n");
		return (1);
	}
	row = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!is_map_line(line))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		map->map[row] = malloc(sizeof(char) * (ft_strlen(line) + 1));
		if (!map->map[row])
		{
			printf("Map row allocation failure!\n");
			return (1);
		}
		strcpy(map->map[row], line);
		row++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

void	print_map(t_map map)
{
	size_t	i;

	i = 0;
	while (i < map.height)
	{
		printf("%s", map.map[i]);
		i++;
	}
}
// checks file extention
void	check_file_extension(char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len < 4 || ft_strncmp(file + len - 4, ".cub", 4))
	{
		printf("give a bratan .cub file.\n");
		exit(1);
	}
}
// empty map
int	empty_map(char *map_file)
{
	int	i;

	i = 0;
	if (!map_file[i])
		return (-1);
	return (0);
}

// check player;
int	check_player(t_map *map)
{
	size_t	i;
	size_t	j;
	int		n;
	int		s;
	int		w;
	int		e;

	n = 0;
	s = 0;
	w = 0;
	e = 0;
	i = 0;
	while (i < map->height)
	{
		map->width = ft_strlen(map->map[i]);
		j = 0;
		while (j < map->width)
		{
			if (map->map[i][j] == 'N')
				n++;
			else if (map->map[i][j] == 'S')
				s++;
			else if (map->map[i][j] == 'W')
				w++;
			else if (map->map[i][j] == 'E')
				e++;
			j++;
		}
		i++;
	}
	if (n == 1 && s == 0 && w == 0 && e == 0)
		return (1);
	else if (n == 0 && s == 1 && w == 0 && e == 0)
		return (2);
	else if (n == 0 && s == 0 && w == 1 && e == 0)
		return (3);
	else if (n == 0 && s == 0 && w == 0 && e == 1)
		return (4);
	else
		return (-1);
}

// check if 3x3
int	checkSize(t_map *map)
{
	size_t	i;

	if (map == NULL || map->map == NULL || map->height < 3)
		return (1);
	i = 0;
	while (i < map->height)
	{
		if (map->map[i] == NULL || strlen(map->map[i]) < 3)
			return (1);
		i++;
	}
	return (0);
}
size_t	get_pos_by_char(t_map *map, char c, char search_char)
{
	size_t	y;
	size_t	x;
	size_t	i;

	i = 0;
	y = 0;
	if (map == NULL || map->map == NULL)
		return (0);
	while (y < map->height)
	{
		map->width = ft_strlen(map->map[i]);
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] == search_char)
			{
				if (c == 'x')
					return (x);
				else
					return (y);
			}
			x++;
		}
		y++;
	}
	return (0);
}
void	check_cords(t_map *map)
{
	if (check_player(map) == 1)
	{
		map->player_x = get_pos_by_char(map, 'x', 'N');
		map->player_y = get_pos_by_char(map, 'y', 'N');
	}
	else if (check_player(map) == 2)
	{
		map->player_x = get_pos_by_char(map, 'x', 'S');
		map->player_y = get_pos_by_char(map, 'y', 'S');
	}
	else if (check_player(map) == 3)
	{
		map->player_x = get_pos_by_char(map, 'x', 'W');
		map->player_y = get_pos_by_char(map, 'y', 'W');
	}
	else if (check_player(map) == 4)
	{
		map->player_x = get_pos_by_char(map, 'x', 'E');
		map->player_y = get_pos_by_char(map, 'y', 'E');
	}
}
void	check_teos_maps(char *map_file)
{
	check_file_extension(map_file);
	if (empty_map(map_file) == -1)
		printf("empty map bruv \n");
}

int	read_map(char *map_file, t_map *map)
{
	int	fd;

	fd = open(map_file, O_RDONLY);
	if (fd == -1 && printf("Error opening the map\n"))
		return (1);
	check_teos_maps(map_file);
	map->height = get_map_height(map_file);
	map->map = malloc(sizeof(char *) * map->height);
	if (!map->map && printf("Map allocation failed!\n"))
		return (1);
	if (get_map_line_width(map_file, map)
		&& printf("Some error occured while reading the map!\n"))
		return (1);
	if (check_player(map) == -1)
		printf("player err \n");
	if (checkSize(map) == 1)
		printf("less then 3x3 \n");
	check_cords(map);
	printf("x cords = %zu, y cords = %zu \n ", map->player_x, map->player_y);
	map->player_char = map->map[map->player_y][map->player_x];
/* 	printf("Value at coordinates (%zu, %zu) is: %c\n", map->player_x,
		map->player_y, map->player_char); */
	close(fd);
	print_map(*map); 
	return (0);
}
