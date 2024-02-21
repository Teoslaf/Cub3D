/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:01:24 by cdurro            #+#    #+#             */
/*   Updated: 2024/02/21 13:49:32 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	if (line[0] == '\n')
		return (0);
	while (line[i] && (line[i] == '\t' || line[i] == ' '))
		i++;
	if (line[i] == '\n' || line[i] == '\0')
		return (0);
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W' && line[i] != '\t'
			&& line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	floor_ceiling_check(char *line, int j, int row, t_map *map)
{
	int	val;

	val = get_color(line + j, map);
	if ((val == 1 && printf("Too many color codes!\n"))
		|| (val == 2 && printf("Wrong color code format!\n"))
		|| (val == 3 && printf("Malloc error!\n")))
	{
		if (row >= 1)
			map->rows_set = row;
		return (1);
	}
	return (0);
}

int	texture_check(char *line, int j, int row, t_map *map)
{
	int	val;

	val = get_texture(line + j, map);
	if ((val == 1 && printf("Too many textures!\n")) || (val == 2
			&& printf("Malloc error!\n")) || (val == 3
			&& printf("Wrong texture format!\n")) || val == 4)
	{
		if (row >= 1)
			map->rows_set = row;
		return (1);
	}
	return (0);
}

int	map_line_check(char *line, int row, t_map *map)
{
	if ((ft_isprint(line[0]) && (line[0] != '\n' || line[0] != '\0'))
		&& printf("Extra info on map file\n"))
	{
		if (row >= 1)
			map->rows_set = row;
		return (1);
	}
	return (0);
}
