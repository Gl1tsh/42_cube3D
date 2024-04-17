/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:33:31 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/04/13 15:49:29 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

#define CUB_EXT    ".cub"

int	file_checker(char *path)
{
	char		buffer;
	int			fd;
	ssize_t		bytesread;

	if (ft_strlen(path) >= ft_strlen(CUB_EXT)
		&& ft_strncmp(path + ft_strlen(path) \
		- ft_strlen(CUB_EXT), CUB_EXT, ft_strlen(CUB_EXT)) != 0)
		return (ERR_FILE_EXTENSION);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ERR_BAD_FILE);
	bytesread = read(fd, &buffer, 1);
	while (bytesread > 0)
	{
		if (ft_strchr(WHITESPACE_CHARSET, buffer) == NULL)
		{
			close(fd);
			return (0);
		}
		bytesread = read(fd, &buffer, 1);
	}
	close(fd);
	return (ERR_FILE_EMPTY);
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
	if (x < 0 || x >= map->width)
		return ('1');
	if (y < 0 || y >= map->height)
		return ('1');
	return (map->bytes[y * map->width + x]);
}

int	parse_map(t_game *game, int fd)
{
	char		*line;
	int			y;
	int			error;

	line = NULL;
	y = 0;
	while (1)
	{
		free(line);
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (is_empty_line(line))
			continue ;
		if (ft_isalpha(line[0]))
		{
			error = pre_parse_texture(game, line);
			if (error)
				return (error);
			continue ;
		}
		ft_memcpy(game->map.bytes + (game->map.width * y++),
			line, ft_strlen(line));
	}
	return (0);
}

int	load_map(t_game *game, char *path_name)
{
	int		fd;
	int		error;

	game->map.width = 0;
	game->map.height = 0;
	error = file_checker(path_name);
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
