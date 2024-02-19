/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_texture_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:04:30 by cdurro            #+#    #+#             */
/*   Updated: 2024/02/08 13:05:56 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	fill_nums(int *i, int *j, char *line, t_map *map)
{
	int	start;

	start = (*i);
	if (line[(*i)] == '-' || line[(*i)] == '+')
		(*i)++;
	while (line[(*i)] && ft_isdigit(line[(*i)]))
		(*i)++;
	if (line[0] == 'F')
		map->floor[++(*j)] = ft_substr(line, start, (*i) - start);
	else
		map->ceiling[++(*j)] = ft_substr(line, start, (*i) - start);
	(*i)--;
}

void	fill(char c, int *j, int **format, t_map *map)
{
	if (c == 'F')
	{
		(*format)[++(*j)] = F;
		map->floor[(*j)] = ft_strdup("F");
	}
	else if (c == 'C')
	{
		(*format)[++(*j)] = C;
		map->ceiling[(*j)] = ft_strdup("C");
	}
	else if (c == ',')
	{
		(*format)[++(*j)] = COMMA;
		if (((*format)[0]) == F)
			map->floor[(*j)] = ft_strdup(",");
		else
			map->ceiling[(*j)] = ft_strdup(",");
	}
}

void	free_floor_ceiling(int j, char c, t_map *map)
{
	int	i;

	if (c == 'F')
	{
		i = 0;
		while (i <= j)
			free(map->floor[i++]);
	}
	else
	{
		i = 0;
		while (i <= j)
			free(map->ceiling[i++]);
	}
}

int	color_format_check(int j, int *format)
{
	if (j != 5 || (format[0] != F && format[0] != C)
		|| format[1] != NUM || format[2] != COMMA || format[3] != NUM
		|| format[4] != COMMA || format[5] != NUM)
		return (1);
	return (0);
}

int	fill_functions(char c, int *j, int **format, t_map *map)
{
	if (color_format_check(*j, *format))
		return (free_floor_ceiling(*j, c, map), 1);
	if (c == 'F')
	{
		map->floor[++(*j)] = 0;
		map->floor_set = 1;
	}
	else
	{
		map->ceiling[++(*j)] = 0;
		map->ceiling_set = 1;
	}
	return (0);
}
