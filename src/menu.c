/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:34:08 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/03/28 19:16:10 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	free_menu(t_game *game)
{
	free_image(&game->menu1_img, game->mlx);
	free_image(&game->menu2_img, game->mlx);
	free_image(&game->menuv_img, game->mlx);
}

void	draw_background(t_game *game)
{
	int	x;

	x = 0;
	while (x < game->width)
	{
		mlx_put_image_to_window(game->mlx, game->win, game->menuv_img.img, x,
			(game->height - game->menuv_img.height) / 2);
		x++;
	}
	game->display_menu = 2;
}

void	draw_menu(t_game *game)
{
	if (game->display_menu == 3)
		draw_background(game);
	if (game->display_menu == 2)
	{
		mlx_put_image_to_window(game->mlx, game->win, game->menu2_img.img,
			(game->width - game->menu2_img.width) / 2,
			(game->height - game->menu2_img.height) / 2);
		game->display_menu = 1;
	}
	else if (game->display_menu == 1)
	{
		mlx_put_image_to_window(game->mlx, game->win, game->menu1_img.img,
			(game->width - game->menu1_img.width) / 2,
			(game->height - game->menu1_img.height) / 2);
		game->display_menu = 2;
	}
}

int	menu_loop(t_game *game, long now)
{
	if (game->keys[KEY_ENTER])
	{
		game->display_menu = 0;
		game->next_frame_ts = 0;
		return (0);
	}
	if (now > game->next_frame_ts)
	{
		draw_menu(game);
		game->next_frame_ts = now + game->frame_delay * 35;
	}
	return (0);
}

int	init_menu(t_game *game)
{
	if (load_image(&game->menu1_img, "assets/menu/menu1.xpm", game->mlx) != 0)
		return (1);
	if (load_image(&game->menu2_img, "assets/menu/menu2.xpm", game->mlx) != 0)
		return (1);
	if (load_image(&game->menuv_img, "assets/menu/menuv.xpm", game->mlx) != 0)
		return (1);
	game->display_menu = 3;
	return (0);
}
