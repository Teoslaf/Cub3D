/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:56:50 by ttaneski          #+#    #+#             */
/*   Updated: 2024/02/08 12:59:33 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	check_file_extension(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 4 || ft_strncmp(file + len - 4, ".cub", 4))
	{
		printf("give a bratan .cub file.\n");
		return (1);
	}
	return (0);
}

int	check_texture_extension(char *file, char **format)
{
	int	i;
	int	len;

	len = ft_strlen(file);
	if (len < 5 || ft_strncmp(file + len - 4, ".xpm", 4))
	{
		printf("give a bratan .xpm file.\n");
		i = -1;
		while (format[++i])
			free(format[i]);
		free(format);
		return (1);
	}
	return (0);
}

int	empty_map(char *map_file)
{
	int	i;

	i = 0;
	if (!map_file[i])
		return (-1);
	return (0);
}

int	check_size(t_map *map)
{
	int	i;

	if (map == NULL || map->map == NULL || map->height < 3)
		return (1);
	i = 0;
	while (i < map->height)
	{
		if (ft_strlen(map->map[i]) < 3)
			return (1);
		i++;
	}
	return (0);
}

int	get_pos_by_char(t_map *map, char c, char search_char)
{
	int	y;
	int	x;

	y = 0;
	if (map == NULL || map->map == NULL)
		return (0);
	while (y < map->height)
	{
		map->width = ft_strlen(map->map[y]) + 1;
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
