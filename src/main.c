/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:36:16 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/03/28 18:31:39 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	load_color(t_image *image, unsigned int color, void *mlx)
{
	int		endian;

	image->width = 1;
	image->height = 1;
	image->img = mlx_new_image(mlx, image->width, image->height);
	image->bytes = mlx_get_data_addr(image->img, &image->bpp, &image->line_size, &endian);
	image->bpp = image->bpp / 8;
	*(unsigned int *)(image->bytes) = color;
	return (0);
}

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
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
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
		game_quit_error(&game, "erreur mlx init");
	if (load_map(&game, argv[1]) != 0)
		game_quit_error(&game, "erreur de map");
	game.player_x = game.map.player_x + 0.5;
	game.player_y = game.map.player_y + 0.5;
	game.win = mlx_new_window(game.mlx, game.width, game.height, "cub3d");
	if (game.win == NULL)
		game_quit_error(&game, "erreur game window");
	create_image(&game.canvas, game.width, game.height, game.mlx);
	if (init_minimap(&game.minimap, game.mlx))
		game_quit_error(&game, "erreur init minimap");
	if (init_menu(&game))
		game_quit_error(&game, "erreur init menu");
	run_game(&game);
	return (1);
}


	// load_anim(&game.katana, 750, 200, (char *[7]) {
	// 	"assets/katana/katana_new_1.xpm",
	// 	"assets/katana/katana_new_2.xpm",
	// 	"assets/katana/katana_new_3.xpm",
	// 	"assets/katana/katana_new_4.xpm",
	// 	"assets/katana/katana_new_3.xpm",
	// 	"assets/katana/katana_new_2.xpm",
	// 		NULL}, game.mlx);