/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaneski <ttaneski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:17:28 by cdurro            #+#    #+#             */
/*   Updated: 2024/02/08 13:14:08 by ttaneski         ###   ########.fr       */
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
int	close_window(t_map *map)
{
	(void)map;
	printf("CLOSING APP\n");
	exit(0);
}

void	init_hooks(t_map *map)
{
	mlx_hook(map->vars.win, 2, 1L << 0, handle_key_down, map);
	mlx_hook(map->vars.win, 17, 0, close_window, map);
}
void	draw_line(t_map *map, int square_x, int square_y, double angle,
		int color)
{
	double	end_x;
	double	end_y;
	double	dx;
	double	dy;
	double	sx;
	double	sy;
	double	err;
	double	e2;

	double player_x = square_x * 25 + 12.5;
	double player_y = square_y * 25 + 12.5;
	end_x = player_x + cos(angle) * 100;
	end_y = player_y + sin(angle) * 100;
	dx = fabs(end_x - player_x);
	dy = fabs(end_y - player_y);
	sx = player_x < end_x ? 1 : -1;
	sy = player_y < end_y ? 1 : -1;
	err = (dx > dy ? dx : -dy) / 2;
	while (1)
	{
		mlx_pixel_put(map->vars.mlx, map->vars.win, (int)player_x,
			(int)player_y, color);
		printf("player_x =%f player_y =%f\n", player_x, player_y);
		if ((int)player_x == (int)end_x && (int)player_y == (int)end_y)
			break ;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			player_x += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			player_y += sy;
		}
	}
}

void	draw_square(t_map *map, int xpos, int ypos, int color)
{
	int i, j;
	for (i = 0; i < 25; i++)
	{
		for (j = 0; j < 25; j++)
		{
			if (i == 0 || j == 0 || i == 24 || j == 24)
			{
				mlx_pixel_put(map->vars.mlx, map->vars.win, xpos + j, ypos + i,
					color);
			}
		}
	}
}

void	minimap(t_map *map)
{
	int	xpos;
	int	ypos;
	int	i;
	int	j;

	int x, y;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < (int)ft_strlen(map->map[y]))
		{
			xpos = x * 25;
			ypos = y * 25;
			i = 0;
			while (i < 25)
			{
				j = 0;
				while (j < 25)
				{
					if (i == 0 || i == 24 || j == 0 || j == 24)
					{
						mlx_pixel_put(map->vars.mlx, map->vars.win, xpos + j,
							ypos + i, 0x808080);
					}
					else
					{
						if (map->map[y][x] == '1')
							mlx_pixel_put(map->vars.mlx, map->vars.win, xpos
								+ j, ypos + i, 0xf3f3f3);
						else if (map->map[y][x] == '0')
							mlx_pixel_put(map->vars.mlx, map->vars.win, xpos
								+ j, ypos + i, 0x00);
						if (map->map[y][x] == map->player_char)
							mlx_pixel_put(map->vars.mlx, map->vars.win, xpos
								+ j, ypos + i, 0xcc0000);
					}
					j++;
				}
				i++;
			}
			x++;
		}
		y++;
	}
	draw_line(map, (double)map->player_x, (double)map->player_y, map->angle, 0xFF0000);
}

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
	{
		printf("Valid Map\n");
		mlx_init();
		init_window(map);
		init_hooks(map);
		map->angle = PI / 4;
		minimap(map);
		// draw_line(map, (double)map->player_x, (double)map->player_y, map->angle,
		// 			0xFF0000);
		mlx_loop(map->vars.mlx);
		free_map(map);
		free(map);
	}
	return (0);
}
