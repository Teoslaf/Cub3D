/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaneski <ttaneski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:17:20 by ttaneski          #+#    #+#             */
/*   Updated: 2024/02/20 14:19:15 by ttaneski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	set_no(t_map *map, char **format)
{
	map->north = ft_strdup(format[1]);
	printf("north text: %s\n", map->north);
	map->textures[NORTH]->img = mlx_xpm_file_to_image(map->vars.mlx, map->north,
			&map->textures[NORTH]->width, &map->textures[NORTH]->height);
	map->textures[NORTH]->address = mlx_get_data_addr(map->textures[NORTH]->img,
			&map->textures[NORTH]->bitxpixel, &map->textures[NORTH]->line_len,
			&map->textures[NORTH]->endian);
	map->textures[NORTH]->xoff = 1;
	map->textures[NORTH]->yoff = 1;
	map->north_set = 1;
}

void	set_so(t_map *map, char **format)
{
	map->south = ft_strdup(format[1]);
	printf("south text: %s\n", map->south);
	map->textures[SOUTH]->img = mlx_xpm_file_to_image(map->vars.mlx, map->south,
			&map->textures[SOUTH]->width, &map->textures[SOUTH]->height);
	map->textures[SOUTH]->address = mlx_get_data_addr(map->textures[SOUTH]->img,
			&map->textures[SOUTH]->bitxpixel, &map->textures[SOUTH]->line_len,
			&map->textures[SOUTH]->endian);
	map->textures[SOUTH]->xoff = 1;
	map->textures[SOUTH]->yoff = 1;
	map->south_set = 1;
}

void	set_ea(t_map *map, char **format)
{
	map->east = ft_strdup(format[1]);
	printf("east text: %s\n", map->east);
	map->textures[EAST]->img = mlx_xpm_file_to_image(map->vars.mlx, map->east,
			&map->textures[EAST]->width, &map->textures[EAST]->height);
	map->textures[EAST]->address = mlx_get_data_addr(map->textures[EAST]->img,
			&map->textures[EAST]->bitxpixel, &map->textures[EAST]->line_len,
			&map->textures[EAST]->endian);
	map->textures[EAST]->xoff = 1;
	map->textures[EAST]->yoff = 1;
	map->east_set = 1;
}

void	set_we(t_map *map, char **format)
{
	map->west = ft_strdup(format[1]);
	printf("west text: %s\n", map->west);
	map->textures[WEST]->img = mlx_xpm_file_to_image(map->vars.mlx, map->west,
			&map->textures[WEST]->width, &map->textures[WEST]->height);
	map->textures[WEST]->address = mlx_get_data_addr(map->textures[WEST]->img,
			&map->textures[WEST]->bitxpixel, &map->textures[WEST]->line_len,
			&map->textures[WEST]->endian);
	map->textures[WEST]->xoff = 1;
	map->textures[WEST]->yoff = 1;
	map->west_set = 1;
}
