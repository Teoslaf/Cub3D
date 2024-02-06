/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaneski <ttaneski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:22:57 by ttaneski          #+#    #+#             */
/*   Updated: 2024/02/06 15:57:24 by ttaneski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_player(t_map *map)
{
	int	i;
	int	j;
	int	direction_count[4];

	direction_count[0] = 0;
	direction_count[1] = 0;
	direction_count[2] = 0;
	direction_count[3] = 0;
	i = 0;
	while (i < map->height)
	{
		map->width = ft_strlen(map->map[i]);
		j = 0;
		while (j < map->width)
		{
			if (map->map[i][j] == 'N')
				direction_count[0]++;
			else if (map->map[i][j] == 'S')
				direction_count[1]++;
			else if (map->map[i][j] == 'W')
				direction_count[2]++;
			else if (map->map[i][j] == 'E')
				direction_count[3]++;
			j++;
		}
		i++;
	}
	if (direction_count[0] == 1 && direction_count[1] == 0
		&& direction_count[2] == 0 && direction_count[3] == 0)
		return (1);
	else if (direction_count[0] == 0 && direction_count[1] == 1
		&& direction_count[2] == 0 && direction_count[3] == 0)
		return (2);
	else if (direction_count[0] == 0 && direction_count[1] == 0
		&& direction_count[2] == 1 && direction_count[3] == 0)
		return (3);
	else if (direction_count[0] == 0 && direction_count[1] == 0
		&& direction_count[2] == 0 && direction_count[3] == 1)
		return (4);
	else
		return (-1);
}

void	check_cords(t_map *map)
{
	map->player_x = 0;
	map->player_y = 0;
	if (check_player(map) == 1)
	{
		map->player_x = get_pos_by_char(map, 'x', 'N');
		map->player_y = get_pos_by_char(map, 'y', 'N');
	}
	else if (check_player(map) == 2)
	{
		map->player_x = get_pos_by_char(map, 'x', 'S');
		map->player_y = get_pos_by_char(map, 'y', 'S');
	}
	else if (check_player(map) == 3)
	{
		map->player_x = get_pos_by_char(map, 'x', 'W');
		map->player_y = get_pos_by_char(map, 'y', 'W');
	}
	else if (check_player(map) == 4)
	{
		map->player_x = get_pos_by_char(map, 'x', 'E');
		map->player_y = get_pos_by_char(map, 'y', 'E');
	}
	map->player_char = '1';
}

void	copy_game(t_map *source, t_map *destination)
{
	int	i;

	destination->height = source->height;
	destination->width = source->width;
	destination->player_y = source->player_y;
	destination->player_x = source->player_x;
	destination->player_char = source->player_char;
	destination->map = (char **)malloc(sizeof(char *) * destination->height);
	if (destination->map == NULL)
	{
		ft_putstr_fd("rip alloc", 1);
		exit(1);
	}
	i = 0;
	while (i < destination->height)
	{
		destination->map[i] = ft_strdup(source->map[i]);
		i++;
	}
}

int	path(t_map *temp, int y, int x)
{
	temp->width = (int)ft_strlen(temp->map[temp->player_y]) - 1;
	if (y < 0 || x < 0 || y >= temp->height || x >= (int)ft_strlen(temp->map[y])
		- 1)
	{
		return (0);
	}
	if (temp->map[y][x] == '1')
	{
		return (0);
	}
	if (temp->map[y][x] == '0' || temp->map[y][x] == 'S'
		|| temp->map[y][x] == 'N' || temp->map[y][x] == 'W'
		|| temp->map[y][x] == 'E')
	{
		if (x == 0 || y == 0 || temp->player_x >= temp->width - 1
			|| temp->player_y >= temp->height - 1)
		{
			printf("on edge\n");
			return (-1);
		}
		if (y == 0 || y == temp->height - 1 || x == 0 || x == temp->width - 1)
		{
			printf("on edge\n");
			return (-1);
		}
		if ((temp->map[y][x + 1] == ' ' || temp->map[y][x - 1] == ' '
				|| temp->map[y - 1][x] == ' ' || temp->map[y + 1][x] == ' '))
		{
			printf("space \n");
			return (-1);
		}
		else if ((temp->map[y][x + 1] == '\t' || temp->map[y][x - 1] == '\t'
				|| temp->map[y - 1][x] == '\t' || temp->map[y + 1][x] == '\t'))
		{
			printf("tab \n");
			return (-1);
		}
		else if ((temp->map[y][x + 1] == '\n' || temp->map[y][x - 1] == '\n'
				|| temp->map[y - 1][x] == '\n' || temp->map[y + 1][x] == '\n'))
		{
			if ((!temp->map[y - 1][x] || temp->map[y - 1][x] == '\n')
				&& printf("GOT 1\n"))
				return (-1);
			if ((!temp->map[y + 1][x] || temp->map[y + 1][x] == '\n')
				&& printf("GOT 2\n"))
				return (-1);
			else if ((temp->map[y][x - 1] == '\n' || temp->map[y][x
				+ 1] == '\n') && (printf("wall hole east\n")))
				return (-1);
		}
	}
	temp->map[y][x] = '1';
	if (y == temp->height - 1 && x == (int)ft_strlen(temp->map[y]) - 1)
		return (1);
	if (path(temp, y, x + 1))
		return (1);
	if (path(temp, y, x - 1))
		return (1);
	if (path(temp, y + 1, x))
		return (1);
	if (path(temp, y - 1, x))
		return (1);
	return (0);
}

int	is_valid_path(t_map *map)
{
	t_map	temp;

	copy_game(map, &temp);
	if (path(&temp, temp.player_y, temp.player_x))
	{
		free_map_double(&temp);
		return (1);
	}
	free_map_double(&temp);
	return (0);
}
