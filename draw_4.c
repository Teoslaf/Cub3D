/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaneski <ttaneski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:56:24 by ttaneski          #+#    #+#             */
/*   Updated: 2024/02/20 14:00:28 by ttaneski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_floor(t_map *map, int floor_color)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_pixel_put(&map->image, x, y, floor_color);
			x++;
		}
		y++;
	}
}

void	draw_ceiling(t_map *map, int ceiling_color)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_pixel_put(&map->image, x, y, ceiling_color);
			x++;
		}
		y++;
	}
}

void	draw_background(t_map *map)
{
	int	ceiling_color;
	int	floor_color;

	ceiling_color = create_rgb(map->ceiling);
	floor_color = create_rgb(map->floor);
	draw_floor(map, floor_color);
	draw_ceiling(map, ceiling_color);
}
