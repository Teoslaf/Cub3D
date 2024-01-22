/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:17:28 by cdurro            #+#    #+#             */
/*   Updated: 2024/01/22 10:55:18 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int main(int argc, char **argv)
{
	t_map map;

	map.height = 0;
	map.width = 0;

	if (argc < 2)
		printf("No map given!\n");
	if (argc > 2)
		printf("Too many arguments\n");
	if (read_map(argv[1], &map))
		printf("Error opening the map\n");
	return  (0);
}