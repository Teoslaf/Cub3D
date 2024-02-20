/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaneski <ttaneski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:17:28 by cdurro            #+#    #+#             */
/*   Updated: 2024/02/20 14:03:49 by ttaneski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	close_window(t_map *map)
{
	(void)map;
	printf("CLOSING APP\n");
	exit(0);
}

int	loop_hook(t_map *map)
{
	show_map(map);
	return (0);
}

int	main(int argc, char **argv)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (1);
	init_window(map);
	init_map(map);
	if (argc < 2)
		printf("No map given!\n");
	if (argc > 2)
		printf("Too many arguments\n");
	if (read_map(argv[1], map))
		printf("Error opening the map\n");
	else
	{
		printf("Valid Map\n");
		printf("map direction: %c\n", map->player.direction);
		set_dir(map);
		init_hooks(map);
		mlx_loop(map->vars.mlx);
	}
	return (0);
}
