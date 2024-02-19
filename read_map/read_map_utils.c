/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaneski <ttaneski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:07:52 by cdurro            #+#    #+#             */
/*   Updated: 2024/02/19 17:02:09 by ttaneski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static int	get_texture_util2(int j, char **format)
{
	int	i;

	if (format[j] && j == 2)
	{
		i = 0;
		while (i < 3)
			free(format[i++]);
		free(format);
		return (1);
	}
	return (0);
}

static int	get_texture_util(char *line, char **format)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = -1;
	while (line[i] && line[i] != '\n')
	{
		if (ft_isalpha(line[i]) || !ft_strncmp(line + i, "./", 2))
		{
			start = i;
			while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'
					|| line[i] == '.' || line[i] == '-' || line[i] == '/'))
				i++;
			format[++j] = ft_substr(line, start, i - start);
			i--;
		}
		if (get_texture_util2(j, format))
			return (1);
		i++;
	}
	format[++j] = 0;
	return (0);
}

static void	get_texture_util4(int i, char **format, t_map *map)
{
	if (!ft_strncmp(format[0], "NO", 2))
	{
		map->north = ft_strdup(format[1]);
		printf("north text: %s\n", map->north);
		map->textures[NORTH]->img = mlx_xpm_file_to_image(map->vars.mlx,
				map->north, &map->textures[NORTH]->width,
				&map->textures[NORTH]->height);
		map->textures[NORTH]->address = mlx_get_data_addr(map->textures[NORTH]->img,
				&map->textures[NORTH]->bitxpixel,
				&map->textures[NORTH]->line_len, &map->textures[NORTH]->endian);
		map->textures[NORTH]->xoff = 1;
		map->textures[NORTH]->yoff = 1;
		map->north_set = 1;
	}
	else if (!ft_strncmp(format[0], "SO", 2))
	{
		map->south = ft_strdup(format[1]);
		map->textures[SOUTH]->img = mlx_xpm_file_to_image(map->vars.mlx,
				map->south, &map->textures[SOUTH]->width,
				&map->textures[SOUTH]->height);
		map->textures[SOUTH]->address = mlx_get_data_addr(map->textures[SOUTH]->img,
				&map->textures[SOUTH]->bitxpixel,
				&map->textures[SOUTH]->line_len, &map->textures[SOUTH]->endian);
		map->south_set = 1;
	}
	else if (!ft_strncmp(format[0], "WE", 2))
	{
		map->west = ft_strdup(format[1]);
		map->textures[WEST]->img = mlx_xpm_file_to_image(map->vars.mlx,
				map->west, &map->textures[WEST]->width,
				&map->textures[WEST]->height);
		map->textures[WEST]->address = mlx_get_data_addr(map->textures[WEST]->img,
				&map->textures[WEST]->bitxpixel, &map->textures[WEST]->line_len,
				&map->textures[WEST]->endian);
		map->west_set = 1;
	}
	else if (!ft_strncmp(format[0], "EA", 2))
	{
		map->east = ft_strdup(format[1]);
		map->textures[EAST]->img = mlx_xpm_file_to_image(map->vars.mlx,
				map->east, &map->textures[EAST]->width,
				&map->textures[EAST]->height);
		map->textures[EAST]->address = mlx_get_data_addr(map->textures[EAST]->img,
				&map->textures[EAST]->bitxpixel, &map->textures[EAST]->line_len,
				&map->textures[EAST]->endian);
		map->east_set = 1;
	}
	while (format[++i])
		free(format[i]);
	free(format);
}

static int	get_texture_util3(char **format, t_map *map)
{
	int	i;

	if (format[1])
	{
		get_texture_util4(-1, format, map);
		return (0);
	}
	else
	{
		i = -1;
		while (format[++i])
			free(format[i]);
		free(format);
		return (3);
	}
}

int	get_texture(char *line, t_map *map)
{
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
		if (check_texture_extension(format[1], format))
			return (3);
	if (get_texture_util3(format, map))
		return (3);
	return (0);
}
