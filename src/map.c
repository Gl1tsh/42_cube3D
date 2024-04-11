/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:33:31 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/04/11 22:24:16 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	extension_checker(char *path)
{
	const char	*extension;

	extension = ".cub";
	if (ft_strlen(path) >= ft_strlen(extension)
		&& ft_strncmp(path + ft_strlen(path) \
		- ft_strlen(extension), extension, ft_strlen(extension)) != 0)
		return (ERR_FILE_EXTENSION);
	return (0);
}

void	free_map(t_game *game)
{
	free(game->map.bytes);
	free_anim(&game->map.ceiling, game->mlx);
	free_anim(&game->map.floor, game->mlx);
	free_anim(&game->map.north, game->mlx);
	free_anim(&game->map.south, game->mlx);
	free_anim(&game->map.east, game->mlx);
	free_anim(&game->map.west, game->mlx);
}

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
	error = extension_checker(path_name);
	if (error)
		return (error);
	fd = open(path_name, O_RDONLY);
	error = measure_map(game, fd);
	close(fd);
	if (error)
		return (error);
	game->map.bytes = malloc(game->map.width * game->map.height);
	if (game->map.bytes == NULL)
		return (ERR_ALLOC_ERROR);
	ft_memset(game->map.bytes, '1', game->map.width * game->map.height);
	fd = open(path_name, O_RDONLY);
	error = parse_map(game, fd);
	close(fd);
	if (error)
		return (error);
	return (check_map(game));
}
