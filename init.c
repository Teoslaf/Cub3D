/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:01:51 by ttaneski          #+#    #+#             */
/*   Updated: 2024/02/21 13:10:54 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_window(t_map *map)
{
	map->vars.win = mlx_new_window(map->vars.mlx, WIDTH, HEIGHT, "Cube3D");
	map->image.img = mlx_new_image(map->vars.mlx, WIDTH, HEIGHT);
	map->image.address = mlx_get_data_addr(map->image.img,
			&map->image.bitxpixel, &map->image.line_len, &map->image.endian);
}

void	init_map2(t_map *map)
{
	map->height = 0;
	map->north_set = 0;
	map->south_set = 0;
	map->west_set = 0;
	map->east_set = 0;
	map->floor_set = 0;
	map->ceiling_set = 0;
	map->map_set = 0;
	map->map_start = 0;
	map->rows_set = 0;
	map->ceiling = NULL;
	map->floor = NULL;
	map->north = NULL;
	map->south = NULL;
	map->west = NULL;
	map->east = NULL;
	map->map = NULL;
}

void	init_player(t_map *map)
{
	map->player.side = 0;
	map->player.dir_x = -1;
	map->player.dir_y = 0;
	map->player.plane_x = 0;
	map->player.plane_y = 0.66;
	map->player.step_x = 0;
	map->player.step_y = 0;
	map->player.delta_dist_x = 0;
	map->player.delta_dist_y = 0;
	map->player.side_dist_x = 0;
	map->player.side_dist_y = 0;
	map->player.perp_wall_dist = 0;
	map->player.ray_dir_x = 0;
	map->player.ray_dir_y = 0;
}

void	init_map(t_map *map)
{
	int	i;

	init_map2(map);
	map->image.img = NULL;
	map->vars.win = NULL;
	map->key.minimap = 0;
	map->key.esc = 0;
	map->key.x_move = 0;
	map->key.y_move = 0;
	map->key.rotate = 0;
	map->mouse.pressed = 0;
	map->textures = malloc(sizeof(t_image) * 4);
	if (!map->textures && printf("Error allocating textures\n"))
		return ;
	i = -1;
	while (++i < 4)
	{
		map->textures[i] = malloc(sizeof(t_image));
		map->textures[i]->img = NULL;
	}
	map->time = 0;
	map->old_time = 0;
}
