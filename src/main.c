/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:36:16 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/03/06 16:17:27 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	load_map(t_map *map, char *path_name)
{
	map->bytes = "111111" "120001" "100021" "100011" "133111";
	map->width = 6;
	map->height = 5;
	map->player_x = 2;
	map->player_y = 2;
	map->celling_color = 0x00aaaaff;
	map->celling_color = 0x00aaffaa;
	map->wall_color = 0x00ff00ff;
	return (0);
}

int	key_pressed(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		game_quit(game);
/*
	else if (keycode == KEY_W)
		move_player(game, 0, -1);
	else if (keycode == KEY_S)
		move_player(game, 0, 1);
	else if (keycode == KEY_A)
		move_player(game, -1, 0);
	else if (keycode == KEY_D)
		move_player(game, 1, 0);
*/
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	game.width = 1024;
	game.height = 600;
	if (load_map(&game.map, argv[1]) != 0)
		game_quit_error(&game, "erreur de map");
	game.mlx = mlx_init();
	if (game.mlx == NULL)
		game_quit_error(&game, "erreur mlx init");
	game.win = mlx_new_window(game.mlx, game.width, game.height, "cub3d");
	if (game.win == NULL)
		game_quit_error(&game, "erreur game window");
	//load_images(&game);
	mlx_hook(game.win, 17, 0, (void *)game_quit, &game);
	mlx_key_hook(game.win, key_pressed, &game);
	mlx_loop(game.mlx);
	return (1);
}
