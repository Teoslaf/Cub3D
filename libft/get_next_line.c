/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:02:59 by cdurro            #+#    #+#             */
/*   Updated: 2024/02/21 12:15:22 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	next_line[BUFFER_SIZE + 1];
	char		*line;
	int			i;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line = ft_strjoin_gnl(0, next_line);
	if (ft_clean(next_line) > 0)
		return (line);
	i = read(fd, next_line, BUFFER_SIZE);
	if (i < 0)
	{
		free(line);
		return (NULL);
	}
	while (i > 0)
	{
		line = ft_strjoin_gnl(line, next_line);
		if (ft_clean(next_line) > 0)
			break ;
		i = read(fd, next_line, BUFFER_SIZE);
	}
	return (line);
}
