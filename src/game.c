/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:31:50 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/03/18 17:10:24 by nagiorgi         ###   ########.fr       */
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
		update_player(game);
		draw_rays(game);
		mlx_put_image_to_window(game->mlx, game->win, game->canvas, 0, 0);
		katana_img = game->katana.current;
		mlx_put_image_to_window(game->mlx, game->win, katana_img->img,
			(game->width - katana_img->width) / 2 + 200,
			(game->height - katana_img->height));
		draw_fps(game, now);
		game->next_frame_ts = now + game->frame_delay;
	}
	return (0);
}
