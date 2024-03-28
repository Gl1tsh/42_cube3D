/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:33:31 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/03/28 17:24:19 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

char	map_get_at(t_map *map, int x, int y)
{
	if (x < 0 || x > map->width)
		return ('1');
	if (y < 0 || y > map->height)
		return ('1');
	return (map->bytes[y * map->width + x]);
}

int	load_map(t_game *game, char *path_name)
{
	int		fd;
	int		error;

	game->map.width = 0;
	game->map.height = 0;
	fd = open(path_name, O_RDONLY);
	error = measure_map(game, fd);
	close(fd);
	if (error)
		return (error);
	game->map.bytes = malloc(game->map.width * game->map.height);
	if (game->map.bytes == NULL)
		return (1);
	ft_memset(game->map.bytes, '1', game->map.width * game->map.height);
	fd = open(path_name, O_RDONLY);
	error = parse_map(game, fd);
	close(fd);
	if (error)
		return (error);
	game->map.player_x = 3;
	game->map.player_y = 1;
	return (0);
}
