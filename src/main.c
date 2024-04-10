/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:36:16 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/04/10 21:40:35 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	key_pressed(int keycode, t_game *game)
{
	game->keys[keycode] = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	game->keys[keycode] = 0;
	return (0);
}

void	run_game(t_game *game)
{
	mlx_hook(game->win, 17, 0, (void *)game_quit, game);
	mlx_hook(game->win, 2, 1L << 0, key_pressed, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_mouse_move(game->win, 0, 0);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
}

int	load_hud(t_game *game)
{
	if (load_image(&game->hud_img, "assets/hud/hud.xpm", game->mlx) != 0)
		return (ERR_HUD);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("t'est con, regarde ton pfd connard\n");
		return (1);
	}
	init_game(&game);
	game.mlx = mlx_init();
	if (game.mlx == NULL)
		game_quit_error(&game, ERR_MLX);
	quit_if_error(&game, load_map(&game, argv[1]));
	quit_if_error(&game, load_hud(&game));
	game.win = mlx_new_window(game.mlx, game.width, game.height, "cub3d");
	if (game.win == NULL)
		game_quit_error(&game, ERR_MLX);
	create_image(&game.canvas, game.width, game.height, game.mlx);
	quit_if_error(&game, init_minimap(&game.minimap, game.mlx));
	quit_if_error(&game, init_menu(&game));
	run_game(&game);
	return (1);
}
