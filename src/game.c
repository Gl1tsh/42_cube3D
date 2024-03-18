/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:31:50 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/03/18 15:23:43 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	rotate_player(t_game *game, double sign)
{
	game->player_angle += game->player_angle_delta * sign;
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

void	update(t_game *game)
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
}

void	draw_fps(t_game *game, int now)
{
	char		fps[9];
	static long	before = 0;

	sprintf(fps, "FPS : %ld", 1000 / (now - before));
	mlx_string_put(game->mlx, game->win, 10, game->height - 20, 0x00ff00, fps);
	before = now;
}

int	game_loop(t_game *game)
{
	long		now;
	t_image		*katana_img;

	now = get_timestamp_ms();
	if (game->display_menu)
		return (menu_loop(game, now));
	if (now > game->next_frame_ts)
	{
		update(game);
		draw_rays(game);
		mlx_put_image_to_window(game->mlx, game->win, game->canvas, 0, 0);
		katana_img = &game->katana_imgs[game->katana_index / 5];
		mlx_put_image_to_window(game->mlx, game->win, katana_img->img,
			(game->width - katana_img->width) / 2 + 200,
			(game->height - katana_img->height));
		game->katana_index = (game->katana_index + 1) % (6 * 5);
		draw_fps(game, now);
		game->next_frame_ts = now + game->frame_delay;
	}
	return (0);
}
