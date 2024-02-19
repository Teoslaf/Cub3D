/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:04:07 by ttaneski          #+#    #+#             */
/*   Updated: 2024/02/07 16:14:51 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	count_directions(t_map *map, int *direction_count)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		map->width = ft_strlen(map->map[i]);
		j = 0;
		while (j < map->width)
		{
			if (map->map[i][j] == 'N')
				direction_count[0]++;
			else if (map->map[i][j] == 'S')
				direction_count[1]++;
			else if (map->map[i][j] == 'W')
				direction_count[2]++;
			else if (map->map[i][j] == 'E')
				direction_count[3]++;
			j++;
		}
		i++;
	}
}

int	check_player_directions(int *direction_count)
{
	if (direction_count[0] == 1 && direction_count[1] == 0
		&& direction_count[2] == 0 && direction_count[3] == 0)
		return (1);
	else if (direction_count[0] == 0 && direction_count[1] == 1
		&& direction_count[2] == 0 && direction_count[3] == 0)
		return (2);
	else if (direction_count[0] == 0 && direction_count[1] == 0
		&& direction_count[2] == 1 && direction_count[3] == 0)
		return (3);
	else if (direction_count[0] == 0 && direction_count[1] == 0
		&& direction_count[2] == 0 && direction_count[3] == 1)
		return (4);
	else
		return (-1);
}

int	check_player(t_map *map)
{
	int	direction_count[4];

	direction_count[0] = 0;
	direction_count[1] = 0;
	direction_count[2] = 0;
	direction_count[3] = 0;
	count_directions(map, direction_count);
	return (check_player_directions(direction_count));
}
