/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaneski <ttaneski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:36:42 by ttaneski          #+#    #+#             */
/*   Updated: 2024/02/20 13:43:26 by ttaneski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_pink_screen(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height * SQUARE)
	{
		x = 0;
		while (x < (map->width - 2) * SQUARE)
		{
			my_pixel_put(&map->image, x, y, 0xD3D3D3);
			x++;
		}
		y++;
	}
}

void	minimap(t_map *map)
{
	int	xpos;
	int	ypos;
	int	x;
	int	y;

	draw_pink_screen(map);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < (int)ft_strlen(map->map[y]) - 1)
		{
			xpos = x * SQUARE;
			ypos = y * SQUARE;
			draw_square(map, xpos, ypos);
			x++;
		}
		y++;
	}
}

t_image	*get_direction_texture(t_map *map)
{
	if (map->player.side == 0)
	{
		if (map->player.ray_dir_x > 0)
			return (map->textures[EAST]);
		else
			return (map->textures[WEST]);
	}
	else
	{
		if (map->player.ray_dir_y > 0)
			return (map->textures[SOUTH]);
		else
			return (map->textures[NORTH]);
	}
}

void	calc(t_map *map, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIDTH - 1;
	map->player.ray_dir_x = map->player.dir_x + map->player.plane_x * camera_x;
	map->player.ray_dir_y = map->player.dir_y + map->player.plane_y * camera_x;
	map->map_x = (int)(map->player.pos_x);
	map->map_y = (int)(map->player.pos_y);
	if (map->player.ray_dir_x == 0)
		map->player.delta_dist_x = 1e30;
	else
		map->player.delta_dist_x = fabs(1 / map->player.ray_dir_x);
	if (map->player.ray_dir_y == 0)
		map->player.delta_dist_y = 1e30;
	else
		map->player.delta_dist_y = fabs(1 / map->player.ray_dir_y);
}

void	calc_stesps(t_map *map, int x)
{
	if (map->player.ray_dir_x < 0)
	{
		map->player.step_x = -1;
		map->player.side_dist_x = (map->player.pos_x - map->map_x)
			* map->player.delta_dist_x;
	}
	else
	{
		map->player.step_x = 1;
		map->player.side_dist_x = (map->map_x + 1.0 - map->player.pos_x)
			* map->player.delta_dist_x;
	}
	if (map->player.ray_dir_y < 0)
	{
		map->player.step_y = -1;
		map->player.side_dist_y = (map->player.pos_y - map->map_y)
			* map->player.delta_dist_y;
	}
	else
	{
		map->player.step_y = 1;
		map->player.side_dist_y = (map->map_y + 1.0 - map->player.pos_y)
			* map->player.delta_dist_y;
	}
}
