/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaneski <ttaneski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:57:50 by cdurro            #+#    #+#             */
/*   Updated: 2024/02/06 12:16:13 by ttaneski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_map(t_map *map)
{
	int	i;

	i = -1;
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
	if (map->map_set)
	{
		i = 0;
		while (i < map->height)
		{
			free(map->map[i]);
			i++;
		}
	}
			// printf("map line: %s\n", map->map[0]);
	
	if (map->map)
		free(map->map);
}

void	free_int_arr(int *arr)
{
	int	i;

	i = 0;
	// while (arr[++i])
	// free(arr[i]);
	free(arr);
}

void	free_map_double(t_map *map)
{
	int i = 0;
	while (i < map->height)
	{
		free(map->map[i]);
		i++;
	}
	free(map->map);
}