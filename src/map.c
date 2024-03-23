/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:33:31 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/03/23 21:08:20 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	load_map(t_map *map, char *path_name)
{
	(void)path_name;
	map->width = 22;
	map->height = 8;
	map->bytes = malloc(map->width * map->height);
	int fd = open("maps/map4.txt", O_RDONLY);
    read(fd, map->bytes, map->width * map->height);
    close(fd);
	map->player_x = 3;
	map->player_y = 1;
	return (0);
}

char	map_get_at(t_map *map, int x, int y)
{
	if (x < 0 || x > map->width)
		return ('1');
	if (y < 0 || y > map->height)
		return ('1');
	return (map->bytes[y * map->width + x]);
}
