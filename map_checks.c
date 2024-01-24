/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaneski <ttaneski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:22:57 by ttaneski          #+#    #+#             */
/*   Updated: 2024/01/24 16:06:18 by ttaneski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// checks file extention

void	check_file_extension(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 4 || ft_strncmp(file + len - 4, ".cub", 4))
	{
		printf("give a bratan .cub file.\n");
		exit(1);
	}
}
// empty map

int	empty_map(char *map_file)
{
	int	i;

	i = 0;
	if (!map_file[i])
		return (-1);
	return (0);
}

// check player;

int	check_player(t_map *map)
{
	int	i;
	int	j;
	int		n;
	int		s;
	int		w;
	int		e;

	n = 0;
	s = 0;
	w = 0;
	e = 0;
	i = 0;
	while (i < map->height)
	{
		map->width = ft_strlen(map->map[i]);
		j = 0;
		while (j < map->width)
		{
			// printf("char L %c\n",map->map[i][j]);
			if (map->map[i][j] == 'N')
				n++;
			else if (map->map[i][j] == 'S')
				s++;
			else if (map->map[i][j] == 'W')
				w++;
			else if (map->map[i][j] == 'E')
				e++;
			j++;
		}
		i++;
	}
	if (n == 1 && s == 0 && w == 0 && e == 0)
		return (1);
	else if (n == 0 && s == 1 && w == 0 && e == 0)
		return (2);
	else if (n == 0 && s == 0 && w == 1 && e == 0)
		return (3);
	else if (n == 0 && s == 0 && w == 0 && e == 1)
		return (4);
	else
		return (-1);
}

// check if 3x3

int	checkSize(t_map *map)
{
	int	i;

	if (map == NULL || map->map == NULL || map->height < 3)
		return (1);
	i = 0;
	while (i < map->height)
	{
		if (map->map[i] == NULL || strlen(map->map[i]) < 3)
			return (1);
		i++;
	}
	return (0);
}

int	get_pos_by_char(t_map *map, char c, char search_char)
{
	int	y;
	int	x;
	int	i;

	i = 0;
	y = 0;
	if (map == NULL || map->map == NULL)
		return (0);
	while (y < map->height)
	{
		map->width = ft_strlen(map->map[i]);
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
	// printf("x cords = %zu, y cords = %zu \n", x, y);
	if (y >= temp->height || x >= (int)ft_strlen(temp->map[y]))
	{
		return (0);
	}
	if (temp->map[y][x] == '1')
	{
		return (0);
	}
	if (temp->map[y][x] == '0')
	{
		if (temp->map[y][x + 1] == ' ' || temp->map[y][x - 1] == ' '
			|| temp->map[y - 1][x] == ' ' || temp->map[y + 1][x] == ' ')
		{
			printf("space \n");
			return(0);
		}
		else if ((temp->map[y][x + 1] == '\t' || temp->map[y][x - 1] == '\t'
				|| temp->map[y - 1][x] == '\t' || temp->map[y + 1][x] == '\t'))
		{
			printf("tab \n");
			return(0);
		}
		else if ((temp->map[y][x + 1] == '\n' || temp->map[y][x - 1] == '\n'
				|| temp->map[y - 1][x] == '\n' || temp->map[y + 1][x] == '\n'))
		{
			printf("new line \n");
			return(0);
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
	if (path(temp, y + 1, x + 1))
		return (1);
	if (path(temp, y + 1, x - 1))
		return (1);
	if (path(temp, y - 1, x + 1))
		return (1);
	if (path(temp, y - 1, x - 1))
		return (1);
	return (0);
}

int	is_valid_path(t_map *map)
{
	t_map	temp;

	copy_game(map, &temp);
	if (path(&temp, temp.player_y, temp.player_x))
	{
		if (temp.player_x == temp.width - 1)
			return (1);
	}
		// print_map(*map);
		// printf("===========================================\n");
		// print_map(temp);
	return (0);
}