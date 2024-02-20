/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaneski <ttaneski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:33:43 by ttaneski          #+#    #+#             */
/*   Updated: 2024/02/20 14:11:08 by ttaneski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	is_hit(t_map *map)
{
	map->hit_wall = 0;
	while (map->hit_wall == 0)
	{
		if (map->player.side_dist_x < map->player.side_dist_y)
		{
			map->player.side_dist_x += map->player.delta_dist_x;
			map->map_x += map->player.step_x;
			map->player.side = 0;
		}
		else
		{
			map->player.side_dist_y += map->player.delta_dist_y;
			map->map_y += map->player.step_y;
			map->player.side = 1;
		}
		if (map->map[map->map_y][map->map_x] == '1')
			map->hit_wall = 1;
	}
	if (map->player.side == 0)
		map->player.perp_wall_dist = (map->player.side_dist_x
				- map->player.delta_dist_x);
	else
		map->player.perp_wall_dist = (map->player.side_dist_y
				- map->player.delta_dist_y);
}

void	quick_math(t_map *map, t_image **tex)
{
	map->line_height = (int)(HEIGHT / map->player.perp_wall_dist);
	map->draw_start = -map->line_height / 2 + HEIGHT / 2;
	map->draw_end = map->line_height / 2 + HEIGHT / 2;
	if (map->player.side == 0)
		map->wall_x = map->player.pos_y + map->player.perp_wall_dist
			* map->player.ray_dir_y;
	else
		map->wall_x = map->player.pos_x + map->player.perp_wall_dist
			* map->player.ray_dir_x;
	map->wall_x -= floor(map->wall_x);
	*tex = get_direction_texture(map);
	map->tex_x = (int)(map->wall_x * (double)(*tex)->width);
	if (map->player.side == 0 && map->player.ray_dir_x > 0)
		map->tex_x = (*tex)->width - map->tex_x - 1;
	if (map->player.side == 1 && map->player.ray_dir_y < 0)
		map->tex_x = (*tex)->width - map->tex_x - 1;
}

void	draw_walls(t_map *map, t_image *tex, int x)
{
	int		y;
	int		index;
	char	*tbuf;

	y = map->draw_start;
	while (y < map->draw_end)
	{
		map->tex_y = (int)(((y - map->draw_start) / (double)(map->draw_end
						- map->draw_start)) * tex->height);
		map->x1 = map->tex_x * tex->xoff;
		map->y1 = map->tex_y * tex->yoff;
		map->x1 = fmod(map->x1, tex->width);
		map->y1 = fmod(map->y1, tex->height);
		if (map->x1 < 0)
			map->x1 += tex->width;
		if (map->y1 < 0)
			map->y1 += tex->height;
		index = ((int)map->y1) * tex->line_len + map->x1
			* (tex->bitxpixel >> 3);
		tbuf = &(tex->address[index]);
		if (y >= 0 && y <= HEIGHT)
			my_pixel_put(&map->image, x, y, (*(int *)tbuf));
		y++;
	}
}

void	show_map(t_map *map)
{
	t_image	*tex;
	int		x;

	x = 0;
	draw_background(map);
	while (x < WIDTH)
	{
		calc(map, x);
		calc_stesps(map, x);
		is_hit(map);
		quick_math(map, &tex);
		map->step = 1.0 * tex->height / map->line_height;
		map->tex_pos = (map->draw_start - HEIGHT / 2 + map->line_height / 2)
			* map->step;
		draw_walls(map, tex, x);
		x++;
	}
	if (map->key.minimap == 1)
		minimap(map);
	mlx_put_image_to_window(map->vars.mlx, map->vars.win, map->image.img, 0, 0);
	handle_movement(map);
	handle_rotation(map);
}

void	set_dir(t_map *map)
{
	if (map->player.direction == 'N')
	{
		map->player.dir_x = 0;
		map->player.dir_y = -1;
	}
	else if (map->player.direction == 'S')
	{
		map->player.dir_x = 0;
		map->player.dir_y = 1;
	}
	else if (map->player.direction == 'W')
	{
		map->player.dir_x = -1;
		map->player.dir_y = 0;
	}
	else if (map->player.direction == 'E')
	{
		map->player.dir_x = 1;
		map->player.dir_y = 0;
	}
	map->player.plane_x = -map->player.dir_y;
	map->player.plane_y = map->player.dir_x;
	map->mouse.curr_x = map->player.dir_x;
	map->mouse.curr_y = map->player.dir_y;
}
