/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:45:52 by ttaneski          #+#    #+#             */
/*   Updated: 2024/02/21 13:53:06 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_hooks(t_map *map)
{
	mlx_hook(map->vars.win, 2, 1L << 0, handle_key_down, map);
	mlx_hook(map->vars.win, 3, 1L << 1, handle_key_up, map);
	mlx_hook(map->vars.win, 4, 1L << 2, mouse_press, map);
	mlx_hook(map->vars.win, 5, 1L << 3, mouse_release, map);
	mlx_hook(map->vars.win, 6, 1L << 8, mouse_move, map);
	mlx_hook(map->vars.win, 17, 0, close_window, map);
	mlx_loop_hook(map->vars.mlx, loop_hook, map);
}

void	my_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->address + (y * image->line_len + x * (image->bitxpixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_player(t_map *map, int xpos, int ypos)
{
	int	i;
	int	j;

	i = 0;
	(void)xpos;
	(void)ypos;
	while (i < PLAYER)
	{
		j = 0;
		while (j < PLAYER)
		{
			my_pixel_put(&map->image, map->player.pos_x * SQUARE + j + 10
				- 12.5, map->player.pos_y * SQUARE + i + 10 - 12.5, 0xc90076);
			j++;
		}
		i++;
	}
}

void	draw_square(t_map *map, int xpos, int ypos)
{
	int	i;
	int	j;

	i = 0;
	(void)ypos;
	(void)xpos;
	while (i < SQUARE - 2)
	{
		j = 0;
		while (j < SQUARE - 2)
		{
			if (map->map[ypos / SQUARE][xpos / SQUARE] == '1')
				my_pixel_put(&map->image, xpos + j, ypos + i, 0xf3f3f3);
			else if (map->map[ypos / SQUARE][xpos / SQUARE] == '0'
				|| map->map[ypos / SQUARE][xpos
				/ SQUARE] == map->player.direction)
				my_pixel_put(&map->image, xpos + j, ypos + i, 0x5b5b5b);
			j++;
		}
		i++;
	}
	i = 0;
	draw_player(map, xpos, ypos);
}

int	create_rgb(char **color)
{
	int	red;
	int	green;
	int	blue;

	red = ft_atoi(color[1]);
	green = ft_atoi(color[3]);
	blue = ft_atoi(color[5]);
	return ((red << 16) + (green << 8) + blue);
}
