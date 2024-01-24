/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaneski <ttaneski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:21:44 by cdurro            #+#    #+#             */
/*   Updated: 2024/01/24 16:19:36 by ttaneski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	is_map_line(char *line)
{
	int	i;

	i = 0;
	if (line[0] == '\n')
		return (0);

	while (line[i] && (line[i] == '\t' || line[i] == ' '))
		i++;
	if (line[i] == '\n')
		return (0);
	while (line[i] && line[i] !='\n')
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W' && line[i] != '\t' && line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

static int	get_map_height(char *map_file)
{
	int		height;
	int		fd;
	char	*line;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		printf("Error opening the map\n");
	height = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!is_map_line(line))
		{
			free(line);
			line = get_next_line(fd);
			continue;
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
	int		i;
	char	*line;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		printf("Error opening the map\n");
	row = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!is_map_line(line))
		{
			if (row > 0)
				map->map_end = row;
			i = 0;
			while (line[i] && (line[i] == ' ' || line[i] == '\t'))
				i++;
			// printf("line: %s\n", line);
			// printf("LAST CHAR: %c\n", (line + i)[ft_strlen(line + i) - 2]);
			if (line[i] == '\n')
				;
			else if (row > 0 && (ft_isprint((line + i)[0]) && (line + i)[0] != '0' && (line + i)[0] != '1') && printf("Map should always be last!\n"))
			{
				if (row >= 1)
					map->rows_set = row;
				return (free(line), 1);
			}
			if ((line + i)[0] == 'F' || (line + i)[0] == 'C')
			{
				int val = get_color(line + i, map);
				if ((val == 1 && printf("Too many color codes!\n")) || (val == 2 && printf("Wrong color code format!\n")) || (val == 3 && printf("Malloc error!\n")))
				{
					if (row >= 1)
						map->rows_set = row;
					return (free(line), 1);
				}
			}
			else if ((line + i)[0] == 'N' || (line + i)[0] == 'S' || (line + i)[0] == 'W' || (line + i)[0] == 'E')
			{
				int val = get_texture(line + i, map);
				if ((val == 1 && printf("Too many textures!\n")) || (val == 2 && printf("Malloc error!\n")) || (val == 3 && printf("Wrong texture format!\n")))
				{
					if (row >= 1)
						map->rows_set = row;
					return (free(line), 1);
				}
			}
			else if (row > 0 && (ft_isprint((line + i)[ft_strlen(line + i) - 2])) && printf("Wrong extra info on map file!\n"))
			{
				if (row >= 1)
					map->rows_set = row;
				return (free(line), 1);
			}
			free(line);
			line = get_next_line(fd);
			continue;
		}
		map->map[row] = ft_strdup(line);
		row++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	map->map_set = 1;
	if (row == 0 && printf("Empty map!\n"))
	{
		map->map_set = 0;
		return (1);
	}
	return (0);
}

void	print_map(t_map map)
{
	int	i;

	i = 0;
	while (map.map[i])
	{
		printf("%s", map.map[i]);
		i++;
	}
}

int	read_map(char *map_file, t_map *map)
{
	int		fd;

	fd = open(map_file, O_RDONLY);
	if (fd == -1 && printf("Error opening the map\n"))
	{
		map->map = NULL;
		return (1);
	}
	check_file_extension(map_file);
	map->height = get_map_height(map_file);
	map->map = malloc(sizeof(char *) * map->height);
	if (!map->map && printf("Map allocation failed!\n"))
		return (1);
	int val = get_map_line_width(map_file, map);
	// printf("val returned: %d\n", val);
	int i = 0;
	if (val)
	{
		int i = 0;

		while (i < map->rows_set)
			free(map->map[i++]);

		return (1);
	}
	if ((!map->north_set && printf("No north texture found!\n")) || (!map->south_set && printf("No south texture found\n")) || (!map->west_set && printf("No west texture found!\n")) || (!map->east_set && printf("No east texture found!\n"))  || (!map->floor_set && printf("No floor info found!\n")) || (!map->ceiling_set && printf("No ceiling info found!\n")))
		return (1);
	// int i;
	i = 0;
	while (map->floor[i])
	{
		if (i == 1 || i == 3 || i == 5)
		{
			int num = ft_atoi(map->floor[i]);
			int num2 = ft_atoi(map->ceiling[i]);

			if (num < 0 || num > 255 || num2 < 0 || num2 > 255)
			{
				printf("Invalid hex code values!\n");
				return (1);
			}
		}
		i++;
	}
	if (check_player(map) == -1)
		printf("player err \n");
	if (checkSize(map) == 1)
		printf("less then 3x3 \n");
	check_cords(map);
	if (map->map && map->player_y < map->height && map->player_x < map->width)
		map->player_char = map->map[map->player_y][map->player_x];
	if(is_valid_path(map) == -1)
		return 1;
	close(fd);
	// i = -1;
	// printf("FLOOR: ");
	// if (map->floor)
	// 	while (map->floor[++i])
	// 		printf("%s ", map->floor[i]);

	// printf("\nCEILING: ");
	// i = -1;
	// if (map->ceiling)
	// 	while (map->ceiling[++i])
	// 		printf("%s ", map->ceiling[i]);
	// if (map->north)
	// 	printf("\nNORTH: %s\n", map->north);
	// if (map->south)
	// 	printf("SOUTH: %s\n", map->south);
	// if (map->west)
	// 	printf("WEST: %s\n", map->west);
	// if (map->east)
	// 	printf("EAST: %s\n", map->east);
	return (0);
}
