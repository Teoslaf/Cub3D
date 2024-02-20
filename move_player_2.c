/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaneski <ttaneski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:42:38 by ttaneski          #+#    #+#             */
/*   Updated: 2024/02/20 14:06:52 by ttaneski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	handle_key_down(int key, t_map *map)
{
	if (key == ESC)
		map->key.esc = 1;
	else if (key == W)
		map->key.y_move = 1;
	else if (key == S)
		map->key.y_move = -1;
	else if (key == A)
		map->key.x_move = -1;
	else if (key == D)
		map->key.x_move = 1;
	else if (key == LEFT_ARROW)
		map->key.rotate = -1;
	else if (key == RIGHT_ARROW)
		map->key.rotate = 1;
	else if (key == MINIMAP)
		map->key.minimap = !map->key.minimap;
	return (0);
}

int	handle_key_up(int key, t_map *map)
{
	if (key == ESC)
		map->key.esc = 0;
	else if (key == W || key == S)
		map->key.y_move = 0;
	else if (key == A || key == D)
		map->key.x_move = 0;
	else if (key == LEFT_ARROW || key == RIGHT_ARROW)
		map->key.rotate = 0;
	return (0);
}

void	handle_movement(t_map *map)
{
	double	step;

	step = 0.2;
	if (map->key.y_move == 1)
		move_forward(map, step);
	else if (map->key.y_move == -1)
		move_backward(map, step);
	else if (map->key.x_move == -1)
		move_left(map, step);
	else if (map->key.x_move == 1)
		move_right(map, step);
	else if (map->key.esc == 1)
		close_window(map);
	else if (map->key.minimap == MINIMAP)
		map->key.minimap = !map->key.minimap;
}

void	handle_rotation(t_map *map)
{
	double	rot;

	rot = 0.1;
	if (map->key.rotate == -1)
		rotate(map, -rot);
	else if (map->key.rotate == 1)
		rotate(map, rot);
	map->player.angle = (int)(atan2(map->player.dir_y, 
				map->player.dir_x) * 180 / PI);
}

int	mouse_move(int x, int y, t_map *map)
{
	double	rot;

	rot = 0.05;
	if (map->mouse.pressed)
	{
		if (x > map->mouse.prev_x)
			rotate(map, rot);
		else
			rotate(map, -rot);
	}
	return (0);
}
