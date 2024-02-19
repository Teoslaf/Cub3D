/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaneski <ttaneski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:21:44 by cdurro            #+#    #+#             */
/*   Updated: 2024/02/19 17:01:43 by ttaneski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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

static int	error_code_check(char *map_file, t_map *map)
{
	int	i;
	int	val;

	val = get_map_line_width(map_file, map);
	if (val)
	{
		if (val == 2 || val == 3)
		{
			i = 0;
			while (i < map->rows_set)
				free(map->map[i++]);
		}
		return (1);
	}
	if ((!map->north_set && printf("No north texture found!\n"))
		|| (!map->south_set && printf("No south texture found\n"))
		|| (!map->west_set && printf("No west texture found!\n"))
		|| (!map->east_set && printf("No east texture found!\n"))
		|| (!map->floor_set && printf("No floor info found!\n"))
		|| (!map->ceiling_set && printf("No ceiling info found!\n")))
		return (1);
	return (0);
}

static int	hex_color_check(t_map *map)
{
	int	i;
	int	num1;
	int	num2;

	i = 0;
	while (map->floor[i])
	{
		if (i == 1 || i == 3 || i == 5)
		{
			num1 = ft_atoi(map->floor[i]);
			num2 = ft_atoi(map->ceiling[i]);
			if ((num1 < 0 || num1 > 255 || num2 < 0 || num2 > 255)
				&& printf("Invalid hex code values!\n"))
				return (1);
		}
		i++;
	}
	return (0);
}

int	read_map(char *map_file, t_map *map)
{
	int	fd;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		return (1);
	if (check_file_extension(map_file) == 1)
		return (1);
	map->height = get_map_height(map_file, map);
	if (map->height == 0 && printf("Empty Map!\n"))
		return (1);
	map->map = malloc(sizeof(char *) * (map->height + 1));
	if (!map->map && printf("Map allocation failed!\n"))
		return (1);
	if (error_code_check(map_file, map) || hex_color_check(map))
		return (1);
	replace_tab_to_space(map->map);
	if ((check_size(map) == 1 && printf("less then 3x3 \n"))
		|| (check_player(map) == -1 && printf("player err \n")))
		return (1);
	check_cords(map);
	if (map->map && map->player_y < map->height && map->player_x < map->width)
		map->player.direction = map->map[map->player_y][map->player_x];
	if (is_valid_path(map) == 1)
		return (1);
	return (close(fd), 0);
}
