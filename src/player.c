/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:45:25 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/04/01 17:38:03 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	rotate_player(t_game *game, double sign)
{
	game->player_angle += game->player_angle_delta * sign;
}

void	rotate_player_mouse(t_game *game)
{
	int			x;
	int			y;
	double		diff;
	static int	old_x;

	mlx_mouse_get_pos(game->win, &x, &y);
	if (old_x == x)
		return ;
	diff = x - old_x;
	if (diff < -500.0)
		diff = -500.0;
	if (diff > 500.0)
		diff = 500.0;
	diff /= 10.0;
	rotate_player(game, diff);
	old_x = x;
}

void	move_player(t_game *game, double angle_delta)
{
	double	delta_x;
	double	delta_y;

	delta_x = cos(game->player_angle + angle_delta) * game->player_speed;
	delta_y = sin(game->player_angle + angle_delta) * game->player_speed;
	if (map_get_at(&game->map, game->player_x
			+ delta_x, game->player_y + delta_y) == '0')
	{
		game->player_x += delta_x;
		game->player_y += delta_y;
	}
}

void	update_player(t_game *game)
{
	if (game->keys[KEY_ESC])
		game_quit(game);
	else if (game->keys[KEY_W])
		move_player(game, 0.0);
	else if (game->keys[KEY_S])
		move_player(game, M_PI);
	else if (game->keys[KEY_A])
		move_player(game, -M_PI_2);
	else if (game->keys[KEY_D])
		move_player(game, M_PI_2);
	if (game->keys[KEY_LEFT])
		rotate_player(game, -1.0);
	else if (game->keys[KEY_RIGHT])
		rotate_player(game, 1.0);
	rotate_player_mouse(game);
}
