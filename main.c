/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaneski <ttaneski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:17:28 by cdurro            #+#    #+#             */
/*   Updated: 2024/01/22 16:46:54 by ttaneski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_map map;
	int i = 0;
	map.height = 0;
	map.width = 0;

	if (argc < 2)
		printf("No map given!\n");
	if (argc > 2)
		printf("Too many arguments\n");
	if (read_map(argv[1], &map))
	{
		printf("Error opening the map\n");
		exit(1);
	}
	while (i < map.height)
		free(map.map[i++]);
	free(map.map);
	return (0);
}