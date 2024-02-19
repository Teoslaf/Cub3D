/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaneski <ttaneski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:54:30 by ttaneski          #+#    #+#             */
/*   Updated: 2024/02/19 16:56:37 by ttaneski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_forward(t_map *map, double step)
{
	if (map->map[(int)(map->player.pos_y + map->player.dir_y
			* step)][(int)map->player.pos_x] != '1')
		map->player.pos_y += map->player.dir_y * step;
	if (map->map[(int)map->player.pos_y][(int)(map->player.pos_x
		+ map->player.dir_x * step)] != '1')
		map->player.pos_x += map->player.dir_x * step;
}

void	move_backward(t_map *map, double step)
{
	if (map->map[(int)(map->player.pos_y - map->player.dir_y
			* step)][(int)map->player.pos_x] != '1')
		map->player.pos_y -= map->player.dir_y * step;
	if (map->map[(int)map->player.pos_y][(int)(map->player.pos_x
		- map->player.dir_x * step)] != '1')
		map->player.pos_x -= map->player.dir_x * step;
}

void	move_left(t_map *map, double step)
{
	double	perp_x;
	double	perp_y;

	perp_x = -map->player.dir_y;
	perp_y = map->player.dir_x;
	if (map->map[(int)(map->player.pos_y - perp_y
			* step)][(int)map->player.pos_x] != '1')
		map->player.pos_y -= perp_y * step;
	if (map->map[(int)map->player.pos_y][(int)(map->player.pos_x - perp_x
		* step)] != '1')
		map->player.pos_x -= perp_x * step;
}

void	move_right(t_map *map, double step)
{
	double	perp_x;
	double	perp_y;

	perp_x = -map->player.dir_y;
	perp_y = map->player.dir_x;
	if (map->map[(int)(map->player.pos_y + perp_y
			* step)][(int)map->player.pos_x] != '1')
		map->player.pos_y += perp_y * step;
	if (map->map[(int)map->player.pos_y][(int)(map->player.pos_x + perp_x
		* step)] != '1')
		map->player.pos_x += perp_x * step;
}
