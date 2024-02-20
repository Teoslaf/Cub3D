/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaneski <ttaneski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:07:52 by cdurro            #+#    #+#             */
/*   Updated: 2024/02/20 14:19:27 by ttaneski         ###   ########.fr       */
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
		if (ft_isalpha(line[i]) || !ft_strncmp(line + i, "./", 2)
			|| !ft_strncmp(line + i, "../", 3))
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
		set_no(map, format);
	else if (!ft_strncmp(format[0], "SO", 2))
		set_so(map, format);
	else if (!ft_strncmp(format[0], "EA", 2))
		set_ea(map, format);
	else if (!ft_strncmp(format[0], "WE", 2))
		set_we(map, format);
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
