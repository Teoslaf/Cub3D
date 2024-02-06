/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaneski <ttaneski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:17:28 by cdurro            #+#    #+#             */
/*   Updated: 2024/02/06 15:37:32 by ttaneski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_window(t_map *map)
{
	map->vars.mlx = mlx_init();
	map->vars.win = mlx_new_window(map->vars.mlx, WIDTH, HEIGHT, "Cube3D");
	map->image.img = mlx_new_image(map->vars.mlx, WIDTH, HEIGHT);
	map->image.address = mlx_get_data_addr(map->image.img,
			&map->image.bitxpixel, &map->image.line_len, &map->image.endian);
}

void	init_map(t_map *map)
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
	// map->player = malloc(sizeof(t_player));
	// map->ray = malloc(sizeof(t_ray));
	map->time = 0;
	map->old_time = 0;
}

// int handle_key_down(int key, t_map *map)
// {
// 	(void)map;
// 	// printf("key pressed: %d\n", key);
// 	if (key == ESC)
// 		close_window(map);
// 	return (0);
// }

// int close_window(t_map *map)
// {
// 	(void)map;
// 	printf("CLOSING APP\n");
// 	exit(0);
// }

// void init_hooks(t_map *map)
// {
// 	mlx_hook(map->vars.win, 2, 1L << 0, handle_key_down, map);
// 	mlx_hook(map->vars.win, 17, 0, close_window, map);
// }

// int create_trgb(int t, int r, int g, int b)
// {
// 	return (t << 24 | r << 16 | g << 8 | b);
// }

// static void init_ray(t_ray *ray)
// {
// 	ray->camera_x = 0;
// 	ray->delta_dist_x = 0;
// 	ray->delta_dist_y = 0;
// 	ray->dir_x = 0;
// 	ray->dir_y = 0;
// 	ray->hit = 0;
// 	ray->side_dist_x = 0;
// 	ray->side_dist_y = 0;
// 	ray->side = 0;
// 	ray->draw_end = 0;
// 	ray->draw_start = 0;
// 	ray->wall_x = 0;
// 	ray->wall_dist = 0;
// 	ray->step_x = 0;
// 	ray->step_y = 0;
// 	ray->line_height = 0;
// }

// static void init_texture(t_texture *texture)
// {
// 	texture->floor = 0;
// 	texture->ceiling = 0;
// 	texture->hex_floor = 0x0;
// 	texture->hex_ceiling = 0x0;
// 	texture->size = 64;
// 	texture->step = 0.0;
// 	texture->pos = 0.0;
// 	texture->x = 0;
// 	texture->y = 0;
// }

// static void init_textures(t_map *map)
// {
// 	int	i;
// 	int	j;

// 	map->textures = calloc(5, sizeof(int));
// 	if (!map->textures)
// 		printf("Texture allocation failed!\n");
// 	map->textures[0] = mlx_xpm_file_to_image(map->vars.mlx, map->north, &i, &j);
// 	map->textures[1] = mlx_xpm_file_to_image(map->vars.mlx, map->south, &i, &j);
// 	map->textures[2] = mlx_xpm_file_to_image(map->vars.mlx, map->east, &i, &j);
// 	map->textures[3] = mlx_xpm_file_to_image(map->vars.mlx, map->west, &i, &j);
// }

// static void init_raycasting_info(int x, t_ray *ray, t_player *player)
// {
// 	init_ray(ray);
// 	ray->camera_x = 2 * x / (double)-1;
// 	ray->dir_x = player->dir_x + player->plane_x * ray->camera_x;
// 	ray->dir_y = player->dir_y + player->plane_y * ray->camera_x;
// 	ray->map_x = player->pos_x;
// 	ray->map_y = player->pos_y;
// 	ray->delta_dist_x = fabs(1 / ray->dir_x);
// 	ray->delta_dist_y = fabs(1 / ray->dir_y);
// }

// static void set_dda(t_ray *ray, t_player *player)
// {
// 	if (ray->dir_x < 0)
// 	{
// 		ray->step_x = -1;
// 		ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x;
// 	}
// 	else
// 	{
// 		ray->step_x = 1;
// 		ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x)
			//* ray->delta_dist_x;
// 	}
// 	if (ray->dir_y < 0)
// 	{
// 		ray->step_y = -1;
// 		ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
// 	}
// 	else
// 	{
// 		ray->step_y = 1;
// 		ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y)
			//* ray->delta_dist_y;
// 	}
// }

// static void perform_dda(t_ray *ray, t_map *map)
// {
// 	while (!ray->hit)
// 	{
// 		if (ray->side_dist_x < ray->side_dist_y)
// 		{
// 			ray->side_dist_x += ray->delta_dist_x;
// 			ray->map_x += ray->step_x;
// 			ray->side = 0;
// 		}
// 		else
// 		{
// 			ray->side_dist_y += ray->delta_dist_y;
// 			ray->map_y += ray->step_y;
// 			ray->side = 1;
// 		}
// 		if (map->map[ray->map_x][ray->map_y] > '0')
// 			ray->hit = 1;
// 	}
// }

// static void calc_line_height(t_ray *ray, t_player *player)
// {
// 	if (ray->side == 0)
// 		ray->wall_dist = (ray->side_dist_x - ray->delta_dist_x);
// 	else
// 		ray->wall_dist = (ray->side_dist_y - ray->delta_dist_y);
// 	ray->line_height = (int)(HEIGHT / ray->wall_dist);
// 	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
// 	if (ray->draw_start < 0)
// 		ray->draw_start = 0;
// 	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
// 	if (ray->draw_end >= HEIGHT)
// 		ray->draw_end = HEIGHT - 1;
// 	if (ray->side == 0)
// 		ray->wall_x = player->pos_y + ray->wall_dist * ray->dir_y;
// 	else
// 		ray->wall_x = player->pos_x + ray->wall_dist * ray->dir_x;
// 	ray->wall_x -= floor(ray->wall_x);
// }

// static void	get_texture_index(t_ray *ray, t_map *map)
// {
// 	if (ray->side == 0)
// 	{
// 		if (ray->dir_x < 0)
// 			map->texture.index = 2;
// 		else
// 			map->texture.index = 3;
// 	}
// 	else
// 	{
// 		if (ray->dir_y < 0)
// 			map->texture.index = 0;
// 		else
// 			map->texture.index = 1;
// 	}
// }

// static void update_texture(int x, t_texture *texure, t_ray *ray, t_map *map)
// {
// 	int	y;
// 	int	color;
// 	(void)x;
// 	texure->x = (int)(ray->wall_x * (double)texure->size);
// 	if ((ray->side == 0 && ray->dir_x > 0) || (ray->side == 1
		//	&& ray->dir_y < 0))
// 		texure->x = texure->size - texure->x - 1;
// 	texure->step = 1.0 * texure->size / ray->line_height;
// 	texure->pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2)
	//	* texure->step;
// 	y = ray->draw_start;
// 	while (y < ray->draw_end)
// 	{
// 		texure->y = (int)texure->pos & (texure->size - 1);
// 		texure->pos += texure->step;
// 		color = map->textures[texure->index][texure->size * texure->y
		//	+ texure->y];
// 		if (texure->index == 0 || texure->index == 3)
// 			color = (color >> 1) & 8355711;

// 	}
// }

// static void render(t_map *map)
// {
// 	t_ray ray;
// 	int x = 0;

// 	while (x < WIDTH)
// 	{
// 		init_raycasting_info(x, &ray, &map->player);
// 		set_dda(&ray, &map->player);
// 		perform_dda(&ray, map);
// 		calc_line_height(&ray, &map->player);
// 		update_texture(x, &map->texture, &ray, map);
// 		x++;
// 	}
// }

int	main(int argc, char **argv)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (3);
	init_map(map);
	if (argc < 2)
		printf("No map given!\n");
	if (argc > 2)
		printf("Too many arguments\n");
	if (read_map(argv[1], map))
		printf("Error opening the map\n");
	else
		printf("Valid Map\n");
	// print_map(map);
	// printf("%s\n", map.map[14]);
	// draw_map(map);
	// init_window(map);
	// init_texture(&map->texture);
	// init_textures(map->textures);
	// init_ray(&map->ray);
	// render(map);
	// init_hooks(map);
	// mlx_loop(map->vars.mlx);
	// for(int i=0; i<map->height; i++)
	// {
	// 	free(map->map[i]);
	// }
	free_map(map);
	free(map);
	return (0);
}
