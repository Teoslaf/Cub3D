/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:17:20 by ttaneski          #+#    #+#             */
/*   Updated: 2024/02/21 13:12:00 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

// void	free_texture_errors(t_map *map)
// {
// 	int	i;
// 	free_texture_text(map);
// 	if (map->north_set)
// 		mlx_destroy_image(map->vars.mlx, map->textures[NORTH]->img);
// 	if (map->south_set)
// 		mlx_destroy_image(map->vars.mlx, map->textures[SOUTH]->img);
// 	if (map->west_set)
// 		mlx_destroy_image(map->vars.mlx, map->textures[WEST]->img);
// 	if (map->east_set)
// 		mlx_destroy_image(map->vars.mlx, map->textures[EAST]->img);
// 	if (map->floor_set)
// 	{
// 		i = -1;
// 		while (map->floor[++i])
// 			free(map->floor[i]);
// 		free(map->floor);
// 	}
// 	if (map->ceiling_set)
// 	{
// 		i = -1;
// 		while (map->ceiling[++i])
// 			free(map->ceiling[i]);
// 		free(map->ceiling);
// 	}
// 	if (map->map_set)
// 	{
// 		i = -1;
// 		while (map->map[++i])
// 			free(map->map[i]);
// 	}
// 	i = -1;
// 	while (++i < 4)
// 		free(map->textures[i]);
// 	free(map->textures);
// 	mlx_destroy_display(map->vars.mlx);
// 	free(map->map);
// 	// free(map);
// }

int	set_no(t_map *map, char **format)
{
	map->north = ft_strdup(format[1]);
	map->textures[NORTH]->img = mlx_xpm_file_to_image(map->vars.mlx, map->north,
			&map->textures[NORTH]->width, &map->textures[NORTH]->height);
	if (!map->textures[NORTH]->img
		&& printf("North texture file doesn't exist\n"))
		return (1);
	map->textures[NORTH]->address = mlx_get_data_addr(map->textures[NORTH]->img,
			&map->textures[NORTH]->bitxpixel, &map->textures[NORTH]->line_len,
			&map->textures[NORTH]->endian);
	map->textures[NORTH]->xoff = 1;
	map->textures[NORTH]->yoff = 1;
	map->north_set = 1;
	return (0);
}

int	set_so(t_map *map, char **format)
{
	map->south = ft_strdup(format[1]);
	map->textures[SOUTH]->img = mlx_xpm_file_to_image(map->vars.mlx, map->south,
			&map->textures[SOUTH]->width, &map->textures[SOUTH]->height);
	if (!map->textures[SOUTH]->img
		&& printf("South texture file doesn't exist\n"))
		return (1);
	map->textures[SOUTH]->address = mlx_get_data_addr(map->textures[SOUTH]->img,
			&map->textures[SOUTH]->bitxpixel, &map->textures[SOUTH]->line_len,
			&map->textures[SOUTH]->endian);
	map->textures[SOUTH]->xoff = 1;
	map->textures[SOUTH]->yoff = 1;
	map->south_set = 1;
	return (0);
}

int	set_we(t_map *map, char **format)
{
	map->west = ft_strdup(format[1]);
	map->textures[WEST]->img = mlx_xpm_file_to_image(map->vars.mlx, map->west,
			&map->textures[WEST]->width, &map->textures[WEST]->height);
	if (!map->textures[WEST]->img && printf("West texture file doesn't exist\n"))
		return (1);
	map->textures[WEST]->address = mlx_get_data_addr(map->textures[WEST]->img,
			&map->textures[WEST]->bitxpixel, &map->textures[WEST]->line_len,
			&map->textures[WEST]->endian);
	map->textures[WEST]->xoff = 1;
	map->textures[WEST]->yoff = 1;
	map->west_set = 1;
	return (0);
}

int	set_ea(t_map *map, char **format)
{
	map->east = ft_strdup(format[1]);
	map->textures[EAST]->img = mlx_xpm_file_to_image(map->vars.mlx, map->east,
			&map->textures[EAST]->width, &map->textures[EAST]->height);
	if (!map->textures[EAST]->img && printf("East texture file doesn't exist\n"))
		return (1);
	map->textures[EAST]->address = mlx_get_data_addr(map->textures[EAST]->img,
			&map->textures[EAST]->bitxpixel, &map->textures[EAST]->line_len,
			&map->textures[EAST]->endian);
	map->textures[EAST]->xoff = 1;
	map->textures[EAST]->yoff = 1;
	map->east_set = 1;
	return (0);
}
