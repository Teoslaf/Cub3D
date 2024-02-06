/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaneski <ttaneski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:57:50 by cdurro            #+#    #+#             */
/*   Updated: 2024/02/06 15:39:00 by ttaneski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_walls(t_map *map)
{
	int	i;

	if (map->north_set)
		free(map->north);
	if (map->south_set)
		free(map->south);
	if (map->west_set)
		free(map->west);
	if (map->east_set)
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

	if (map->map_set)
	{
		i = 0;
		while (i < map->height)
		{
			free(map->map[i]);
			i++;
		}
		free(map->map);
	}
}

void	free_map(t_map *map)
{
	free_walls(map);
	free_map_grid(map);
}

void	free_int_arr(int *arr)
{
	free(arr);
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
