/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaneski <ttaneski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:52:09 by ttaneski          #+#    #+#             */
/*   Updated: 2024/02/08 13:15:40 by ttaneski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	redraw_map(t_map *map)
{
	mlx_clear_window(map->vars.mlx, map->vars.win);
	minimap(map);
}

t_map	*moves_up(t_map *map)
{
	if (map->map[map->player_y - 1][map->player_x] == '0')
	{
		map->map[map->player_y - 1][map->player_x] = map->player_char;
		map->map[map->player_y][map->player_x] = '0';
		map->player_y -= 1;
	}
	return (map);
}

t_map	*moves_down(t_map *map)
{
	if (map->map[map->player_y + 1][map->player_x] == '0')
	{
		map->map[map->player_y + 1][map->player_x] = map->player_char;
		map->map[map->player_y][map->player_x] = '0';
		map->player_y += 1;
	}
	return (map);
}

t_map	*moves_left(t_map *map)
{
	if (map->map[map->player_y][map->player_x - 1] == '0')
	{
		map->map[map->player_y][map->player_x - 1] = map->player_char;
		map->map[map->player_y][map->player_x] = '0';
		map->player_x -= 1;
	}
	return (map);
}

t_map	*moves_right(t_map *map)
{
	if (map->map[map->player_y][map->player_x + 1] == '0')
	{
		map->map[map->player_y][map->player_x + 1] = map->player_char;
		map->map[map->player_y][map->player_x] = '0';
		map->player_x += 1;
	}
	return (map);
}

int	handle_arrow_down(int key, t_map *map)
{
	if (key == UP_ARROW)
	{
		// moves_up(map);
		redraw_map(map);
	}
	if (key == DOWN_ARROW)
	{
		// moves_down(map);
		redraw_map(map);
	}
	if (key == LEFT_ARROW)
	{
		// moves_left(map);
		map->angle -= 0.1;
		redraw_map(map);
	}
	if (key == RIGHT_ARROW)
	{
		// moves_right(map);
		map->angle += 0.1;
		redraw_map(map);
	}
	return (0);
}

int	handle_key_down(int key, t_map *map)
{
	if (key == ESC)
		close_window(map);
	if (key == W)
	{
		moves_up(map);
		redraw_map(map);
	}
	if (key == S)
	{
		moves_down(map);
		redraw_map(map);
	}
	if (key == A)
	{
		moves_left(map);
		redraw_map(map);
	}
	if (key == D)
	{
		moves_right(map);
		redraw_map(map);
	}
	handle_arrow_down(key, map);
	return (0);
}