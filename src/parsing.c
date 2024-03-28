/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 19:20:03 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/03/28 12:56:27 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	parse_texture(t_game *game, char *line)
{
	char	**parts;
	int		i;

	parts = ft_split(line, ' ');
	if (ft_strcmp(parts[0], "NO") == 0)
		load_anim(&game->map.north, 0, 100000, parts + 1, game->mlx);
	if (ft_strcmp(parts[0], "SO") == 0)
		load_anim(&game->map.south, 0, 100000, parts + 1, game->mlx);
	if (ft_strcmp(parts[0], "WE") == 0)
		load_anim(&game->map.west, 0, 100000, parts + 1, game->mlx);
	if (ft_strcmp(parts[0], "EA") == 0)
		load_anim(&game->map.east, 0, 100000, parts + 1, game->mlx);
	if (ft_strcmp(parts[0], "F") == 0)
		load_anim(&game->map.floor, 0, 100000, parts + 1, game->mlx);
	if (ft_strcmp(parts[0], "C") == 0)
		load_anim(&game->map.ceiling, 0, 100000, parts + 1, game->mlx);
	i = 0;
	while (parts[i] != NULL)
		free(parts[i++]);
	free(parts);
	return (0);
}

int	check_texture(int *counters, char *line)
{
	char	**parts;
	int		i;

	parts = ft_split(line, ' ');
	if (ft_strcmp(parts[0], "NO") == 0)
		counters[0]++;
	if (ft_strcmp(parts[0], "SO") == 0)
		counters[1]++;
	if (ft_strcmp(parts[0], "WE") == 0)
		counters[2]++;
	if (ft_strcmp(parts[0], "EA") == 0)
		counters[3]++;
	if (ft_strcmp(parts[0], "F") == 0)
		counters[4]++;
	if (ft_strcmp(parts[0], "C") == 0)
		counters[5]++;
	i = 0;
	while (parts[i] != NULL)
		free(parts[i++]);
	free(parts);
	return (0);
}

int	load_map(t_game *game, char *path_name)
{
	static int	counters[6] = {0, 0, 0, 0, 0, 0};
	char		*line;
	int			width;
	int			height;
	int			y;
	int			fd;

	width = 0;
	height = 0;
	line = NULL;
	fd = open(path_name, O_RDONLY);
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
			line[ft_strlen(line) - 1] = '\0';
			check_texture(counters, line);
			continue ;
		}
		if (ft_strlen(line) > width)
			width = ft_strlen(line);
		height++;
	}
	close(fd);
	y = 0;
	while (y < 6)
		if (counters[y++] != 1)
			return (122);
	game->map.width = width;
	game->map.height = height;
	game->map.bytes = malloc(game->map.width * game->map.height);
	ft_memset(game->map.bytes, '1', game->map.width * game->map.height);
	fd = open(path_name, O_RDONLY);
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
			line[ft_strlen(line) - 1] = '\0';
			parse_texture(game, line);
			continue ;
		}
		ft_memcpy(game->map.bytes + (width * y), line, ft_strlen(line));
		y++;
	}
	close(fd);
	game->map.player_x = 3;
	game->map.player_y = 1;
	return (0);
}
