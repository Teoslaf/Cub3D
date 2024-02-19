/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:03:34 by cdurro            #+#    #+#             */
/*   Updated: 2024/02/08 13:06:34 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static int	num_check(int i, int j, char *line, int **format)
{
	if ((ft_isdigit(line[i]) || ((line[i] == '-' || line[i] == '+')
				&& ft_isdigit(line[i + 1]))) && i != 0 && ((*format)[j] == F
		|| (*format)[j] == C || (*format)[j] == COMMA))
		return (1);
	return (0);
}

static int	fill_color_arr(char *line, int **format, t_map *map)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (line[++i] && line[i] != '\n')
	{
		if ((line[i] == 'F' || line[i] == 'C') && i == 0)
			fill(line[i], &j, format, map);
		else if (num_check(i, j, line, format))
		{
			fill_nums(&i, &j, line, map);
			(*format)[j] = NUM;
		}
		else if (line[i] == ',' && (*format)[j] == NUM)
			fill(line[i], &j, format, map);
		else if (line[i] != ' ' && line[i] != '\t')
			return (free_floor_ceiling(j, line[0], map), 1);
		if (j >= 6)
			return (free_floor_ceiling(j, line[0], map), 1);
	}
	if (fill_functions(line[0], &j, format, map))
		return (1);
	return (0);
}

static int	color_allocations(char c, int **format, t_map *map)
{
	(*format) = ft_calloc(7, sizeof(int));
	if (!(*format))
		return (1);
	if (c == 'F')
	{
		map->floor = malloc(sizeof(char *) * 7);
		if (!map->floor)
			return (1);
	}
	else
	{
		map->ceiling = malloc(sizeof(char *) * 7);
		if (!map->ceiling)
			return (1);
	}
	return (0);
}

static void	fill_color_arr_error(char c, int **format, t_map *map)
{
	if (c == 'F')
	{
		free(map->floor);
		map->floor = NULL;
		map->floor_set = 0;
	}
	else
	{
		free(map->ceiling);
		map->ceiling = NULL;
		map->ceiling_set = 0;
	}
	free((*format));
}

int	get_color(char *line, t_map *map)
{
	int	*format;

	if ((line[0] == 'F' && map->floor_set) || (line[0] == 'C'
			&& map->ceiling_set))
		return (1);
	if (line[1] != ' ' && line[1] != '\t')
		return (2);
	if (color_allocations(line[0], &format, map))
		return (3);
	if (fill_color_arr(line, &format, map))
	{
		fill_color_arr_error(line[0], &format, map);
		return (2);
	}
	free(format);
	return (0);
}
