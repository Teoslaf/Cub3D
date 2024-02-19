/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:53:24 by cdurro            #+#    #+#             */
/*   Updated: 2024/02/07 16:16:38 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static int	count_tabs(char *line, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == c)
			count++;
		i++;
	}
	return (count);
}

static void	replace_util(char *line, char **new_line, int *i, int *j)
{
	if (line[(*j)] == '\t')
	{
		(*new_line)[(*i)] = ' ';
		(*new_line)[(*i) + 1] = ' ';
		(*new_line)[(*i) + 2] = ' ';
		(*new_line)[(*i) + 3] = ' ';
		(*i) += 3;
	}
	else
		(*new_line)[(*i)] = line[(*j)];
	(*i)++;
	(*j)++;
}

static char	*replace(char *line, int tabs)
{
	int		i;
	int		j;
	int		len;
	char	*new_line;

	len = (tabs * 4) + ft_strlen(line) - tabs - 1;
	new_line = malloc(sizeof(char) * len + 2);
	if (!new_line)
		return (NULL);
	i = 0;
	j = 0;
	while (i <= len)
		replace_util(line, &new_line, &i, &j);
	new_line[i] = '\0';
	free(line);
	return (new_line);
}

void	replace_tab_to_space(char **map)
{
	int	i;
	int	tabs;

	i = 0;
	while (map[i])
	{
		tabs = count_tabs(map[i], '\t');
		map[i] = replace(map[i], tabs);
		i++;
	}
}
