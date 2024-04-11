/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 19:20:03 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/04/12 00:54:02 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	parse_texture(t_game *game, char *line)
{
	char	**parts;

	parts = ft_split(line, ' ');
	if (ft_strcmp(parts[0], "NO") == 0)
		if (load_anim(&game->map.south, 0, parts + 1, game->mlx) != 0)
			return (free_array(parts, ERR_TEXTURE_NORTH));
	if (ft_strcmp(parts[0], "SO") == 0)
		if (load_anim(&game->map.north, 0, parts + 1, game->mlx) != 0)
			return (free_array(parts, ERR_TEXTURE_SOUTH));
	if (ft_strcmp(parts[0], "WE") == 0)
		if (load_anim(&game->map.east, 60, parts + 1, game->mlx) != 0)
			return (free_array(parts, ERR_TEXTURE_WEST));
	if (ft_strcmp(parts[0], "EA") == 0)
		if (load_anim(&game->map.west, 0, parts + 1, game->mlx) != 0)
			return (free_array(parts, ERR_TEXTURE_EAST));
	if (ft_strcmp(parts[0], "F") == 0)
		if (load_anim(&game->map.floor, 0, parts + 1, game->mlx) != 0)
			return (free_array(parts, ERR_TEXTURE_FLOOR));
	if (ft_strcmp(parts[0], "C") == 0)
		if (load_anim(&game->map.ceiling, 0, parts + 1, game->mlx) != 0)
			return (free_array(parts, ERR_TEXTURE_CEILING));
	if (ft_strcmp(parts[0], "K") == 0)
		load_anim(&game->katana, 30, parts + 1, game->mlx);
	return (free_array(parts, 0));
}

int	check_texture(int *counters, char *line)
{
	char	**parts;

	parts = ft_split(line, ' ');
	if (ft_strcmp(parts[0], "NO") == 0 && parts[1] != NULL)
		counters[0]++;
	if (ft_strcmp(parts[0], "SO") == 0 && parts[1] != NULL)
		counters[1]++;
	if (ft_strcmp(parts[0], "WE") == 0 && parts[1] != NULL)
		counters[2]++;
	if (ft_strcmp(parts[0], "EA") == 0 && parts[1] != NULL)
		counters[3]++;
	if (ft_strcmp(parts[0], "F") == 0 && parts[1] != NULL)
		counters[4]++;
	if (ft_strcmp(parts[0], "C") == 0 && parts[1] != NULL)
		counters[5]++;
	return (free_array(parts, 0));
}

int	check_texture_counts(int *counters)
{
	int	i;

	i = 0;
	while (i < 6)
		if (counters[i++] != 1)
			return (ERR_MISSING_INFORMATION);
	return (0);
}

int	pre_parse_texture(t_game *game, char *line)
{
	int	error;

	line[ft_strlen(line) - 1] = '\0';
	error = parse_texture(game, line);
	if (error)
	{
		free(line);
		return (error);
	}
	return (0);
}

int	measure_map(t_game *game, int fd)
{
	static int	counters[6] = {0, 0, 0, 0, 0, 0};
	char		*line;

	line = NULL;
	while (1)
	{
		free(line);
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (game->map.width == 0 && is_empty_line(line))
			continue ;
		if (ft_isalpha(line[0]))
		{
			line[ft_strlen(line) - 1] = '\0';
			check_texture(counters, line);
			continue ;
		}
		if (is_empty_line(line))
			return (ERR_EMPTY_LINE_IN_MAP);
		if ((int)ft_strlen(line) > game->map.width)
			game->map.width = ft_strlen(line);
		game->map.height++;
	}
	return (check_texture_counts(counters));
}
