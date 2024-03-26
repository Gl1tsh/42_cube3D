/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 19:20:03 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/03/26 20:20:17 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	load_map(t_map *map, char *path_name)
{
	char	*line;
	int		width;
	int		height;
	int		y;
	int		fd;

	width = 0;
	height = 0;
	fd = open(path_name, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		if (ft_strlen(line) > width)
			width = ft_strlen(line);

		height++;
		free(line);
	}
	close(fd);
	map->width = width;
	map->height = height;
	map->bytes = malloc(map->width * map->height);
	ft_memset(map->bytes, '1', map->width * map->height);
	fd = open(path_name, O_RDONLY);
	y = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		ft_memcpy(map->bytes + (width * y), line, ft_strlen(line));
		y++;
		free(line);
	}
    close(fd);
	map->player_x = 3;
	map->player_y = 1;
	return (0);
}
