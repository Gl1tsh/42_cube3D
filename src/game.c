/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:31:50 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/03/28 18:29:10 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	draw_fps(t_game *game, int now)
{
	char		fps[9];
	static long	before = 0;

	sprintf(fps, "FPS : %ld", 1000 / (now - before));
	mlx_string_put(game->mlx, game->win, 10, game->height - 20, 0x00ff00, fps);
	before = now;
}

void	init_game(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	game->precision = 128.0;
	game->half_fov = M_PI_2 / 3.0;
	game->player_angle = M_PI_2;
	game->player_speed = 0.15;
	game->player_angle_delta = 0.05;
	game->width = 1024;
	game->height = 640;
	game->frame_delay = 1000 / FPS;
	game->angle_increment = 2 * game->half_fov / game->width;
	ft_memset(game->keys, 0, 256);
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
		update_anim(&game->katana, now);
		update_anim(&game->map.north, now);
		update_anim(&game->map.south, now);
		update_anim(&game->map.east, now);
		update_anim(&game->map.west, now);
		update_player(game);
		draw_rays(game);
		mlx_put_image_to_window(game->mlx, game->win, game->canvas.img, 0, 0);
		// katana_img = game->katana.current;
		// mlx_put_image_to_window(game->mlx, game->win, katana_img->img,
		// 	(game->width - katana_img->width) / 2 + 200,
		// 	(game->height - katana_img->height));
		draw_minimap(&game->minimap, game);
		draw_fps(game, now);
		game->next_frame_ts = now + game->frame_delay;
	}
	return (0);
}
