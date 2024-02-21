/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaneski <ttaneski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:07:52 by cdurro            #+#    #+#             */
/*   Updated: 2024/02/21 14:06:17 by ttaneski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	get_texture_util2(int j, char **format)
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

int	get_texture_util(char *line, char **format)
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

void	free_format(int i, char **format)
{
	while (format[++i])
		free(format[i]);
	free(format);
}

int	get_texture_util4(int i, char **format, t_map *map)
{
	if (!ft_strncmp(format[0], "NO", 2))
	{
		if (set_no(map, format))
			return (free_format(i, format), 1);
	}
	else if (!ft_strncmp(format[0], "SO", 2))
	{
		if (set_so(map, format))
			return (free_format(i, format), 1);
	}
	else if (!ft_strncmp(format[0], "EA", 2))
	{
		if (set_ea(map, format))
			return (free_format(i, format), 1);
	}
	else if (!ft_strncmp(format[0], "WE", 2))
	{
		if (set_we(map, format))
			return (free_format(i, format), 1);
	}
	return (free_format(i, format), 0);
}

int	get_texture_util3(char **format, t_map *map)
{
	int	i;

	if (format[1])
	{
		if (get_texture_util4(-1, format, map))
			return (4);
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
