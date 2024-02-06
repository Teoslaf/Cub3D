/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaneski <ttaneski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:07:52 by cdurro            #+#    #+#             */
/*   Updated: 2024/02/06 15:33:06 by ttaneski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	fill_nums(int *i, int *j, char *line, t_map *map)
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

static void	fill(char c, int *j, int **format, t_map *map)
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

static int	fill_color_arr(char *line, int **format, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (line[i] && line[i] != '\n')
	{
		if ((line[i] == 'F' || line[i] == 'C') && i == 0)
			fill(line[i], &j, format, map);
		else if ((ft_isdigit(line[i]) || ((line[i] == '-' || line[i] == '+')
					&& ft_isdigit(line[i + 1]))) && i != 0 && ((*format)[j] == F
				|| (*format)[j] == C || (*format)[j] == COMMA))
		{
			fill_nums(&i, &j, line, map);
			(*format)[j] = NUM;
		}
		else if (line[i] == ',' && (*format)[j] == NUM)
			fill(line[i], &j, format, map);
		else if (line[i] == ' ' || line[i] == '\t')
			;
		else
		{
			if (line[0] == 'F')
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
			return (1);
		}
		if (j >= 6)
		{
			if (line[0] == 'F')
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
			return (1);
		}
		i++;
	}
	if (j != 5 || ((*format)[0] != F && (*format)[0] != C)
		|| (*format)[1] != NUM || (*format)[2] != COMMA || (*format)[3] != NUM
		|| (*format)[4] != COMMA || (*format)[5] != NUM)
	{
		if (line[0] == 'F')
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
		return (1);
	}
	if (line[0] == 'F')
	{
		map->floor[++j] = 0;
		map->floor_set = 1;
	}
	else
	{
		map->ceiling[++j] = 0;
		map->ceiling_set = 1;
	}
	return (0);
}

int	get_color(char *line, t_map *map)
{
	int	*format;

	if ((line[0] == 'F' && map->floor_set) || (line[0] == 'C'
			&& map->ceiling_set))
		return (1);
	if (line[1] != ' ' && line[1] != '\t')
		return (2);
	format = ft_calloc(7, sizeof(int));
	if (!format)
		return (3);
	if (line[0] == 'F')
	{
		map->floor = malloc(sizeof(char *) * 7);
		if (!map->floor)
			return (3);
	}
	else
	{
		map->ceiling = malloc(sizeof(char *) * 7);
		if (!map->ceiling)
			return (3);
	}
	if (fill_color_arr(line, &format, map))
	{
		if (line[0] == 'F')
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
		free(format);
		return (2);
	}
	free(format);
	return (0);
}

int	get_texture(char *line, t_map *map)
{
	int i;
	int j;
	int start;
	char **format;

	if (!ft_strncmp(line, "NO", 2) && map->north_set)
		return (1);
	else if (!ft_strncmp(line, "SO", 2) && map->south_set)
		return (1);
	else if (!ft_strncmp(line, "WE", 2) && map->west_set)
		return (1);
	else if (!ft_strncmp(line, "EA", 2) && map->east_set)
		return (1);
	format = malloc(sizeof(char *) * 3);
	if (!format)
		return (2);

	i = 0;
	j = -1;
	while (line[i] && line[i] != '\n')
	{
		if (ft_isalpha(line[i]))
		{
			start = i;
			while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'
					|| line[i] == '.' || line[i] == '-' || line[i] == '/'))
				i++;
			format[++j] = ft_substr(line, start, i - start);
			i--;
		}
		else if (!ft_strncmp(line + i, "./", 2))
		{
			start = i;
			i += 2;
			while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'
					|| line[i] == '-' || line[i] == '.' || line[i] == '/'))
				i++;
			format[++j] = ft_substr(line, start, i - start);
			i--;
		}
		if (format[j] && j == 2)
		{
			i = 0;
			while (i < 3)
				free(format[i++]);
			free(format);
			return (3);
		}
		i++;
	}
	format[++j] = 0;
	if (format[1])
	{
		if (check_texture_extension(format[1]) != 0)
		{
			i = -1;
			while (format[++i])
				free(format[i]);
			free(format);
			return (3);
		}
	}
	if (format[1])
	{
		if (!ft_strncmp(format[0], "NO", 2))
		{
			map->north = ft_strdup(format[1]);
			map->north_set = 1;
		}
		else if (!ft_strncmp(format[0], "SO", 2))
		{
			map->south = ft_strdup(format[1]);
			map->south_set = 1;
		}
		else if (!ft_strncmp(format[0], "WE", 2))
		{
			map->west = ft_strdup(format[1]);
			map->west_set = 1;
		}
		else if (!ft_strncmp(format[0], "EA", 2))
		{
			map->east = ft_strdup(format[1]);
			map->east_set = 1;
		}
		i = -1;
		while (format[++i])
			free(format[i]);
		free(format);
		return (0);
	}
	else
	{
		i = -1;
		while (format[++i])
			free(format[i]);
		free(format);
		return (3);
	}
}