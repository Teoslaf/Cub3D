/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaneski <ttaneski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:17:28 by cdurro            #+#    #+#             */
/*   Updated: 2024/01/24 16:14:00 by ttaneski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int main(int argc, char **argv)
{
	t_map map;

	map.height = 0;
	map.north_set = 0;
	map.south_set = 0;
	map.west_set = 0;
	map.east_set = 0;
	map.floor_set = 0;
	map.ceiling_set = 0;
	map.map_set = 0;
	map.map_end = 0;
	map.rows_set = 0;
	map.ceiling = NULL;
	map.floor = NULL;
	map.north = NULL;
	map.south = NULL;
	map.west = NULL;
	map.east = NULL;
	map.map = NULL;

	if (argc < 2)
		printf("No map given!\n");
	if (argc > 2)
		printf("Too many arguments\n");
	if (read_map(argv[1], &map))
		printf("Error opening the map\n");
	else
		printf("Valid Map\n");
	// print_map(map);
	// printf("%s\n", map.map[14]);

	free_map(&map);
	return  (0);
}