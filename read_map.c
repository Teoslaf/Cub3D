/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:21:44 by cdurro            #+#    #+#             */
/*   Updated: 2024/01/31 16:28:51 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int is_map_line(char *line)
{
	int i;

	i = 0;
	if (line[0] == '\n')
		return (0);
	while (line[i] && (line[i] == '\t' || line[i] == ' '))
		i++;
	if (line[i] == '\n')
		return (0);
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W' && line[i] != '\t' && line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

static int get_map_height(char *map_file, t_map *map)
{
	int height;
	int fd;
	int i;
	int row;
	char *line;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		printf("Error opening the map\n");
	height = 0;
	row = 1;
	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		if ((line[i] == '0' || line[i] == '1') || ((line[i] == 'S' || line[i] == 'N' || line[i] == 'W' || line[i] == 'E') && (line[i + 1] == '0' || line[i + 1] == '1')))
		{
			printf("line stopped: %s\n", line);
			break;
		}
		row++;
		free(line);
		line = get_next_line(fd);
	}
	// line = get_next_line(fd);
	while (line)
	{
	
		printf("line go on: %s\n", line);
		i = 0;
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		if (((line[0] == '\n' || line[0] == '\0')) && height > 0)
		{
			free(line);
			break;
		}
		height++;
		row++;
		free(line);
		line = get_next_line(fd);
	}
	map->map_start = row - height;
	printf("map start: %d\n", map->map_start);
	printf("height: %d\n", height);
	close(fd);
	return (height);
}

static int get_map_line_width(char *map_file, t_map *map)
{
	int row;
	int fd;
	int i;
	int j;
	char *line;

	fd = open(map_file, O_RDONLY);
	if (fd == -1 && printf("Error opening the map\n"))
		return (-1);
	row = 0;
	line = get_next_line(fd);
	i = 1;
	while (line && i < map->map_start)
	{
		j = 0;
		while (line[j] && (line[j] == ' ' || line[j] == '\t'))
			j++;
		printf("line 1: %s\n", line + j);
		printf("i: %d\n", i);
		if ((line + j)[0] == 'F' || (line + j)[0] == 'C')
		{
			int val = get_color(line + j, map);
			if ((val == 1 && printf("Too many color codes!\n")) || (val == 2 && printf("Wrong color code format!\n")) || (val == 3 && printf("Malloc error!\n")))
			{
				if (row >= 1)
					map->rows_set = row;
				return (free(line), 1);
			}
		}
		else if ((line + j)[0] == 'N' || (line + j)[0] == 'S' || (line + j)[0] == 'W' || (line + j)[0] == 'E')
		{
			int val = get_texture(line + j, map);
			if ((val == 1 && printf("Too many textures!\n")) || (val == 2 && printf("Malloc error!\n")) || (val == 3 && printf("Wrong texture format!\n")))
			{
				if (row >= 1)
					map->rows_set = row;
				return (free(line), 1);
			}
		}
		else if ((ft_isprint(line[0]) && (line[0] != '\n' || line[0] != '\0')) && printf("Extra info on map file\n"))
		{
			if (row >= 1)
				map->rows_set = row;
			return (free(line), 1);
		}
		i++;
		free(line);
		line = get_next_line(fd);
	}
	i = 0;
	while (line && i < map->height)
	{
		printf("line 2: %s\n", line);
		if (!is_map_line(line) && printf("Extra info on map\n"))
		{
			if (row >= 1)
				map->rows_set = row;
			return (free(line), 1);
		}
		map->map[row] = ft_strdup(line);
		row++;
		i++;
		free(line);
		line = get_next_line(fd);
	}
	while (line)
	{
		i = 0;
		while (line[i] && (line[i] == '\t' || line[i] == ' '))
			i++;
		printf("line 3: %s\n", line + i);
		if (ft_isprint(line[i]) && (line[i] != '\n' && line[i] != '\t' && line[i] != ' ') && printf("Map should always be last!\n"))
		{
			if (row >= 1)
				map->rows_set = row;
			return (free(line), 1);
		}
		free(line);
		line = get_next_line(fd);
	}
	map->map[row] = 0;
	map->map_set = 1;
	close(fd);
	return (0);
}

void print_map(t_map map)
{
	int i;

	i = 0;
	while (map.map[i])
	{
		printf("%s", map.map[i]);
		i++;
	}
}

int	count_tabs(char *line, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == c)
			count++;
		i++;
	}
	return (count);
}

char	*replace(char *line, int tabs)
{
	int	i;
	int	j;
	int	len;
	char	*new_line;

	len = (tabs * 4) + ft_strlen(line) - tabs - 1;
	// printf("len: %d\n", len);
	new_line = malloc(sizeof(char) * len);
	if (!new_line)
		return (NULL);
	i = 0;
	j = 0;
	while (i <= len)
	{
		// printf("i: %d | j: %d\n", i, j);
		if (line[j] == '\t')
		{
			new_line[i] = ' ';
			new_line[i + 1] = ' ';
			new_line[i + 2] = ' ';
			new_line[i + 3] = ' ';
			i += 3;
		}
		else
			new_line[i] = line[j];
		i++;
		j++;
	}
	new_line[i] = '\0';
	// printf("new line: %s\n", new_line);
	return (new_line);
}

void	replace_tab_to_space(char **map)
{
	int	i;
	int	tabs;

	i = 0;
	while (map[i])
	{
		tabs = count_tabs(map[i], '\t');
		// printf("tabs: %d | line: %s\n", tabs, map[i]);
		map[i] = replace(map[i], tabs);
		i++;
	}
}

int read_map(char *map_file, t_map *map)
{
	int fd;

	fd = open(map_file, O_RDONLY);
	if (fd == -1 && printf("Error opening the map\n"))
	{
		map->map = NULL;
		return (1);
	}
	check_file_extension(map_file);
	map->height = get_map_height(map_file, map);
	if (map->height == 0 && printf("Empty Map!\n"))
		return (1);
	map->map = malloc(sizeof(char *) * (map->height + 1));
	if (!map->map && printf("Map allocation failed!\n"))
		return (1);
	int val = get_map_line_width(map_file, map);
	printf("val returned: %d\n", val);
	int i = 0;
	if (val)
	{
		int i = 0;

		while (i < map->rows_set)
			free(map->map[i++]);

		return (1);
	}
	if ((!map->north_set && printf("No north texture found!\n")) || (!map->south_set && printf("No south texture found\n")) || (!map->west_set && printf("No west texture found!\n")) || (!map->east_set && printf("No east texture found!\n")) || (!map->floor_set && printf("No floor info found!\n")) || (!map->ceiling_set && printf("No ceiling info found!\n")))
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
	replace_tab_to_space(map->map);
	if (checkSize(map) == 1 && printf("less then 3x3 \n"))
		return (1);
	if (check_player(map) == -1 && printf("player err \n"))
		return (1);
	check_cords(map);
	if (map->map && map->player_y < map->height && map->player_x < map->width)
		map->player_char = map->map[map->player_y][map->player_x];
	if (is_valid_path(map) == 1)
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
