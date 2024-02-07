/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaneski <ttaneski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:22:57 by ttaneski          #+#    #+#             */
/*   Updated: 2024/02/07 11:34:24 by ttaneski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

int	is_valid_poss(t_map *temp, int y, int x)
{
	if (x == 0 || y == 0 || temp->player_x >= temp->width - 1
		|| temp->player_y >= temp->height - 1)
		return (-1);
	if (y == 0 || y == temp->height - 1 || x == 0 || x == temp->width - 1)
		return (-1);
	if (temp->map[y][x + 1] == ' ' || temp->map[y][x - 1] == ' ' || temp->map[y
		- 1][x] == ' ' || temp->map[y + 1][x] == ' ')
		return (-1);
	else if (temp->map[y][x + 1] == '\t' || temp->map[y][x - 1] == '\t'
		|| temp->map[y - 1][x] == '\t' || temp->map[y + 1][x] == '\t')
		return (-1);
	else if (temp->map[y][x + 1] == '\n' || temp->map[y][x - 1] == '\n'
		|| temp->map[y - 1][x] == '\n' || temp->map[y + 1][x] == '\n')
	{
		if (!temp->map[y - 1][x] || temp->map[y - 1][x] == '\n')
			return (-1);
		if (!temp->map[y + 1][x] || temp->map[y + 1][x] == '\n')
			return (-1);
		else if ((temp->map[y][x - 1] == '\n' || temp->map[y][x + 1] == '\n'))
			return (-1);
	}
	return (0);
}

int	path(t_map *temp, int y, int x)
{
	temp->width = (int)ft_strlen(temp->map[temp->player_y]) - 1;
	if (y < 0 || x < 0 || y >= temp->height || x >= (int)ft_strlen(temp->map[y])
		- 1)
		return (0);
	if (temp->map[y][x] == '1')
		return (0);
	temp->map[y][x] = '1';
	if (y == temp->height - 1 && x == (int)ft_strlen(temp->map[y]) - 1)
		return (1);
	if (is_valid_poss(temp, y, x) == -1)
	{
		printf("not surrounded  by walls, etc \n");
		return (-1);
	}
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
