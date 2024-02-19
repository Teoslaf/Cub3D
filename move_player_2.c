/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaneski <ttaneski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:42:38 by ttaneski          #+#    #+#             */
/*   Updated: 2024/02/19 16:58:31 by ttaneski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	handle_key_down(int key, t_map *map)
{
	if (key == ESC)
		close_window(map);
	else if (key == W || key == S || key == A || key == D)
		handle_movement(key, map);
	else if (key == LEFT_ARROW || key == RIGHT_ARROW)
		handle_rotation(key, map);
	else if (key == MINIMAP)
		map->minimap = !map->minimap;
	redraw_map(map);
	return (0);
}

void	handle_movement(int key, t_map *map)
{
	double	step;

	step = 0.2;
	if (key == W)
		move_forward(map, step);
	else if (key == S)
		move_backward(map, step);
	else if (key == A)
		move_left(map, step);
	else if (key == D)
		move_right(map, step);
}

void	handle_rotation(int key, t_map *map)
{
	double	rot;

	rot = 0.1;
	if (key == LEFT_ARROW)
		rotate(map, -rot);
	else if (key == RIGHT_ARROW)
		rotate(map, rot);
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
		redraw_map(map);
	}
	return (0);
}
