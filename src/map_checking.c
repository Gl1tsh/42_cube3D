/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:04:18 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/04/10 21:00:20 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	find_player(t_game *game)
{
	int		i;
	char	*cardinal_point;

	cardinal_point = "ESWN";
	i = 0;
	while (i < game->map.width * game->map.height)
	{
		if (game->map.bytes[i] == 'N' || game->map.bytes[i] == 'S'
			|| game->map.bytes[i] == 'E' || game->map.bytes[i] == 'W')
		{
			game->map.player_x = i % game->map.width;
			game->map.player_y = i / game->map.width;
			game->player_x = game->map.player_x + 0.5;
			game->player_y = game->map.player_y + 0.5;
			game->player_angle = (ft_strchr(cardinal_point, game->map.bytes[i])
					- cardinal_point) * M_PI_2;
			game->map.bytes[i] = '0';
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_invalid_char(t_game *game)
{
	int		i;

	i = 0;
	while (i < game->map.width * game->map.height)
	{
		if (game->map.bytes[i] != '1' && game->map.bytes[i] != '0'
			&& !ft_strchr(WHITESPACE_CHARSET, game->map.bytes[i]))
			return (1);
		i++;
	}
	return (0);
}

int	flood_fill(t_game *game, char *map_copy, int x, int y)
{
	if (x < 0 || x >= game->map.width || y < 0 || y >= game->map.height)
		return (1);
	if (ft_strchr(WHITESPACE_CHARSET, map_copy[y * game->map.width + x]))
		return (1);
	if (map_copy[y * game->map.width + x] == '1'
		|| map_copy[y * game->map.width + x] == '-' )
		return (0);
	map_copy[y * game->map.width + x] = '-';
	if (flood_fill(game, map_copy, x - 1, y) != 0)
		return (1);
	if (flood_fill(game, map_copy, x + 1, y) != 0)
		return (1);
	if (flood_fill(game, map_copy, x, y - 1) != 0)
		return (1);
	if (flood_fill(game, map_copy, x, y + 1) != 0)
		return (1);
	return (0);
}

int	check_bounds(t_game *game)
{
	char	*map_copy;

	map_copy = malloc(game->map.width * game->map.height);
	if (map_copy == NULL)
		return (1);
	ft_memcpy(map_copy, game->map.bytes, game->map.width * game->map.height);
	if (flood_fill(game, map_copy, game->map.player_x, game->map.player_y) != 0)
	{
		free(map_copy);
		return (1);
	}
	free(map_copy);
	return (0);
}

int	check_map(t_game *game)
{
	if (game->map.width < 3 || game->map.height < 3)
		return (ERR_MAP_SIZE_TOO_SMALL);
	if (find_player(game) != 0)
		return (ERR_PLAYER_MISSING);
	if (check_invalid_char(game) != 0)
		return (ERR_INVALID_CHAR);
	if (check_bounds(game) != 0)
		return (ERR_MAP_BORDERS);
	return (0);
}
