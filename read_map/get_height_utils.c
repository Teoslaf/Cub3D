/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_height_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaneski <ttaneski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:59:44 by cdurro            #+#    #+#             */
/*   Updated: 2024/02/21 14:01:16 by ttaneski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static int	get_map_height_util(char **line, int *row, int fd)
{
	int	i;

	while ((*line))
	{
		i = 0;
		while ((*line)[i] && ((*line)[i] == ' ' || (*line)[i] == '\t'))
			i++;
		if (((*line)[i] == '0' || (*line)[i] == '1') || (((*line)[i] == 'S'
			|| (*line)[i] == 'N' || (*line)[i] == 'W' || (*line)[i] == 'E')
			&& ((*line)[i + 1] == '0' || (*line)[i + 1] == '1')))
			return (0);
		(*row)++;
		free((*line));
		(*line) = get_next_line(fd);
	}
	return (1);
}

static void	get_map_height_util_2(char **line, int *row, int *height, int fd)
{
	int	i;
	int	map_height_set;

	map_height_set = 0;
	while ((*line))
	{
		i = 0;
		while ((*line)[i] && ((*line)[i] == ' ' || (*line)[i] == '\t'))
			i++;
		if ((((*line)[0] == '\n' || (*line)[0] == '\0')) && (*height) > 0)
		{
			free((*line));
			(*line) = get_next_line(fd);
			map_height_set = 1;
			continue ;
		}
		if (!map_height_set)
			(*height)++;
		(*row)++;
		free((*line));
		(*line) = get_next_line(fd);
	}
}

int	get_map_height(char *map_file, t_map *map)
{
	int		height;
	int		fd;
	int		row;
	char	*line;

	fd = open(map_file, O_RDONLY);
	if (fd == -1 && printf("Error opening the map\n"))
		return (-1);
	height = 0;
	row = 1;
	line = get_next_line(fd);
	if (get_map_height_util(&line, &row, fd)
		&& printf("Error in get_map_height_utils\n"))
		return (-1);
	map->map_start = row;
	get_map_height_util_2(&line, &row, &height, fd);
	close(fd);
	return (height);
}
