/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:17:28 by cdurro            #+#    #+#             */
/*   Updated: 2024/02/21 14:47:35 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	close_window(t_map *map)
{
	free_map(map);
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

	if (argc != 2 && printf("Invalid number of arguments\n"))
		return (1);
	map = malloc(sizeof(t_map));
	if (!map)
		return (1);
	map->vars.mlx = mlx_init();
	init_map(map);
	if (read_map(argv[1], map) && printf("Error opening the map\n"))
		free_map(map);
	else
	{
		printf("Valid Map\n");
		init_window(map);
		set_dir(map);
		init_hooks(map);
		mlx_loop(map->vars.mlx);
	}
	return (0);
}
