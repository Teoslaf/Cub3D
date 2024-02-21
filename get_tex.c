/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaneski <ttaneski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:02:38 by ttaneski          #+#    #+#             */
/*   Updated: 2024/02/21 14:05:09 by ttaneski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_texture(char *line, t_map *map)
{
	int		val;
	char	**format;

	if ((!ft_strncmp(line, "NO", 2) && map->north_set) || (!ft_strncmp(line,
				"SO", 2) && map->south_set) || (!ft_strncmp(line, "WE", 2)
			&& map->west_set) || (!ft_strncmp(line, "EA", 2) && map->east_set))
		return (1);
	format = malloc(sizeof(char *) * 3);
	if (!format)
		return (2);
	if (get_texture_util(line, format))
		return (3);
	if (format[1])
		if (check_texture_extension(format[1], format, map))
			return (3);
	val = get_texture_util3(format, map);
	if (val == 4)
		return (4);
	else if (val > 0)
		return (3);
	return (0);
}
