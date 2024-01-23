/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaneski <ttaneski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:18:49 by cdurro            #+#    #+#             */
/*   Updated: 2024/01/23 10:58:46 by ttaneski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <unistd.h>
#include <math.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft/libft.h"
#include "get_next_line.h"

typedef struct s_map
{
	size_t	width;
	size_t	height;
	size_t 	player_x;
	size_t 	player_y;
	char	**map;
}		t_map;

int	read_map(char *map_file, t_map *map);

#endif