/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:57:50 by cdurro            #+#    #+#             */
/*   Updated: 2024/01/24 14:32:14 by cdurro           ###   ########.fr       */
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
			free(map->map[i++]);
	}
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