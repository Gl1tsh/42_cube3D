/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:04:18 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/03/29 15:59:57 by nagiorgi         ###   ########.fr       */
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

int	check_map(t_game *game)
{
	if (find_player(game) != 0)
		return (1);
	return (0);
}
