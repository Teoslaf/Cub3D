/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:04:48 by cdurro            #+#    #+#             */
/*   Updated: 2024/02/19 10:06:34 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static int	before_map(char *line, int j, int *row, t_map *map)
{
	if ((line + j)[0] == 'F' || (line + j)[0] == 'C')
	{
		if (floor_ceiling_check(line, j, *row, map))
			return (1);
	}
	else if ((line + j)[0] == 'N' || (line + j)[0] == 'S' || (line
		+ j)[0] == 'W' || (line + j)[0] == 'E')
	{
		if (texture_check(line, j, *row, map))
			return (1);
	}
	else if (map_line_check(line, *row, map))
		return (1);
	return (0);
}

static int	check_before_map(char **line, int fd, int *row, t_map *map)
{
	int	i;
	int	j;

	i = 1;
	while ((*line) && i < map->map_start)
	{
		j = 0;
		while ((*line)[j] && ((*line)[j] == ' ' || (*line)[j] == '\t'))
			j++;
		if (((*line) + j)[0] == '\n')
		{
			free((*line));
			(*line) = get_next_line(fd);
			(*row)++;
			i++;
			continue ;
		}
		if (before_map((*line), j, row, map))
			return (free((*line)), 1);
		i++;
		free(*line);
		*line = get_next_line(fd);
	}
	return (0);
}

static int	check_in_map(char **line, int fd, int *row, t_map *map)
{
	int	i;

	i = 0;
	while ((*line) && i < map->height)
	{
		if (!is_map_line((*line)) && printf("Extra info on map\n"))
		{
			if ((*row) >= 1)
				map->rows_set = (*row);
			return (free((*line)), 1);
		}
		map->map[i] = ft_strdup((*line));
		(*row)++;
		i++;
		free((*line));
		(*line) = get_next_line(fd);
	}
	map->map[i] = 0;
	map->map_set = 1;
	return (0);
}

static int	check_after_map(char **line, int fd, int *row, t_map *map)
{
	int	i;

	while ((*line))
	{
		i = 0;
		while ((*line)[i] && ((*line)[i] == '\t' || (*line)[i] == ' '))
			i++;
		if (ft_isprint((*line)[i]) && ((*line)[i] != '\n' && (*line)[i] != '\t'
				&& (*line)[i] != ' ') && printf("Map should always be last!\n"))
		{
			if ((*row) >= 1)
				map->rows_set = (*row);
			return (free((*line)), 1);
		}
		free((*line));
		(*line) = get_next_line(fd);
	}
	return (0);
}

int	get_map_line_width(char *map_file, t_map *map)
{
	int		row;
	int		fd;
	char	*line;

	fd = open(map_file, O_RDONLY);
	if (fd == -1 && printf("Error opening the map\n"))
		return (-1);
	row = 0;
	line = get_next_line(fd);
	while (!ft_strncmp(line, "\n", 1))
	{
		free(line);
		line = get_next_line(fd);
	}
	if (check_before_map(&line, fd, &row, map)
		&& printf("Error in checking before map\n"))
		return (1);
	if (check_in_map(&line, fd, &row, map))
		return (2);
	if (check_after_map(&line, fd, &row, map))
		return (3);
	close(fd);
	return (0);
}
