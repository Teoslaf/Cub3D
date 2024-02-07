/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaneski <ttaneski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:52:09 by ttaneski          #+#    #+#             */
/*   Updated: 2024/02/07 15:53:17 by ttaneski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


void	redraw_map(t_map *map)
{
	mlx_clear_window(map->vars.mlx, map->vars.win);
	minimap(map);
}

t_map	*move_player(t_map *map, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = map->player_x + dx;
	new_y = map->player_y + dy;
	if (map->map[new_y][new_x] == '0')
	{
		map->map[new_y][new_x] = map->player_char;
		map->map[map->player_y][map->player_x] = '0';
		map->player_x = new_x;
		map->player_y = new_y;
	}
	return (map);
}

int	handle_key_down(int key, t_map *map)
{
	if (key == ESC)
		close_window(map);
	else if (key == W)
		move_player(map, 0, -1);
	else if (key == S)
		move_player(map, 0, 1);
	else if (key == A)
		move_player(map, -1, 0);
	else if (key == D)
		move_player(map, 1, 0);
	return (0);
}