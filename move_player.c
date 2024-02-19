/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaneski <ttaneski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:52:09 by ttaneski          #+#    #+#             */
/*   Updated: 2024/02/19 17:00:45 by ttaneski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	redraw_map(t_map *map)
{
	mlx_destroy_image(map->vars.mlx, map->image.img);
	map->image.img = mlx_new_image(map->vars.mlx, WIDTH, HEIGHT);
	show_map(map);
}

int	handle_arrow_down(int key, t_map *map)
{
	if (key == LEFT_ARROW)
	{
		map->angle -= 0.1;
		if (map->angle < 0)
			map->angle = 2 * PI;
		redraw_map(map);
	}
	if (key == RIGHT_ARROW)
	{
		map->angle += 0.1;
		if (map->angle > 2 * PI)
			map->angle = 0;
		redraw_map(map);
	}
	return (0);
}

int	rotate(t_map *map, double angle)
{
	double	old_dir_x;
	double	old_plane_xx;

	old_dir_x = map->player.dir_x;
	old_plane_xx = map->player.plane_x;
	map->player.dir_x = old_dir_x * cos(angle) - map->player.dir_y * sin(angle);
	map->player.dir_y = old_dir_x * sin(angle) + map->player.dir_y * cos(angle);
	map->player.plane_x = old_plane_xx * cos(angle) - map->player.plane_y
		* sin(angle);
	map->player.plane_y = old_plane_xx * sin(angle) + map->player.plane_y
		* cos(angle);
	return (0);
}

int	mouse_press(int button, int x, int y, t_map *map)
{
	if (button == 1)
	{
		map->mouse.prev_x = x;
		map->mouse.prev_y = y;
		map->mouse.pressed = 1;
	}
	return (0);
}

int	mouse_release(int button, int x, int y, t_map *map)
{
	if (button == 1)
	{
		map->mouse.curr_x = x;
		map->mouse.curr_y = y;
		map->mouse.pressed = 0;
	}
	return (0);
}
