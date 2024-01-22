/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:21:44 by cdurro            #+#    #+#             */
/*   Updated: 2024/01/22 12:16:20 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	is_map_line(char *line)
{
	if ((ft_strchr(line, '0') || ft_strchr(line, '1')) && !ft_strchr(line, 'F') && !ft_strchr(line, 'C'))
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
		printf("Error opening the map\n");
	height = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!is_map_line(line))
		{
			line = get_next_line(fd);
			continue;
		}
		height++;
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
		printf("Error opening the map\n");
	row = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!is_map_line(line))
		{
			line = get_next_line(fd);
			continue;
		}
		map->map[row] = malloc(sizeof(char) * ft_strlen(line));
		if (!map->map[row] && printf("Map row allocation failure!\n"))
			return (1);
		map->map[row] = line;
		row++;
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

void	print_map(t_map map)
{
	int	i;

	i = 0;
	while (i < map.height)
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
		return (1);
	map->height = get_map_height(map_file);
	map->map = malloc(sizeof(char *) * map->height);
	if (!map->map && printf("Map allocation failed!\n"))
		return (1);

	if (get_map_line_width(map_file, map) && printf("Some error occured while reading the map!\n"))
		return (1);
	close(fd);
	
	print_map(*map);
	return (0);
}
