/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:57:50 by cdurro            #+#    #+#             */
/*   Updated: 2024/02/21 15:04:20 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_texture_text(t_map *map)
{
	if (map->north)
		free(map->north);
	if (map->south)
		free(map->south);
	if (map->west)
		free(map->west);
	if (map->east)
		free(map->east);
}

void	free_walls(t_map *map)
{
	int	i;

	if (map->north)
		free(map->north);
	if (map->south)
		free(map->south);
	if (map->west)
		free(map->west);
	if (map->east)
		free(map->east);
	if (map->floor_set)
	{
		i = -1;
		while (map->floor[++i])
			free(map->floor[i]);
		free(map->floor);
	}
	if (map->ceiling_set)
	{
		i = -1;
		while (map->ceiling[++i])
			free(map->ceiling[i]);
		free(map->ceiling);
	}
}

void	free_map_grid(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		if (map->map[i])
			free(map->map[i]);
		i++;
	}
	if (map->map)
		free(map->map);
}

void	free_map(t_map *map)
{
	int	i;

	free_walls(map);
	free_map_grid(map);
	i = -1;
	while (++i < 4)
	{
		if (map->textures[i]->img)
			mlx_destroy_image(map->vars.mlx, map->textures[i]->img);
		free(map->textures[i]);
	}
	free(map->textures);
	if (map->image.img)
		mlx_destroy_image(map->vars.mlx, map->image.img);
	if (map->vars.win)
		mlx_destroy_window(map->vars.mlx, map->vars.win);
	mlx_destroy_display(map->vars.mlx);
	free(map->vars.mlx);
	free(map);
}

void	free_map_double(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		free(map->map[i]);
		i++;
	}
	free(map->map);
}
