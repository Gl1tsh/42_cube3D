/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:36:16 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/03/18 16:43:47 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <string.h>

#define ft_memset memset

int	load_image(t_image *image, char *filename, void *mlx)
{
	int		endian;

	image->img = mlx_xpm_file_to_image(mlx, filename, &image->width, &image->height);
	image->bytes = mlx_get_data_addr(image->img, &image->bpp, &image->line_size, &endian);
	image->bpp = image->bpp / 8;
	return (0);
}

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

int	main(int argc, char **argv)
{
	(void)argc;
	t_game	game;
	int		endian;

	game.precision = 128.0;
	game.half_fov = M_PI_2 / 3.0;
	game.player_angle = M_PI_2;
	game.player_speed = 0.05;
	game.player_angle_delta = 0.05;
	game.width = 1280;
	game.height = 740;
	game.frame_delay = 1000 / FPS;
	game.angle_increment = 2 * game.half_fov / game.width;
	ft_memset(game.keys, 0, 256);
	if (load_map(&game.map, argv[1]) != 0)
		game_quit_error(&game, "erreur de map");
	game.player_x = game.map.player_x + 0.5;
	game.player_y = game.map.player_y + 0.5;
	game.mlx = mlx_init();
	if (game.mlx == NULL)
		game_quit_error(&game, "erreur mlx init");
	game.win = mlx_new_window(game.mlx, game.width, game.height, "cub3d");
	if (game.win == NULL)
		game_quit_error(&game, "erreur game window");
	game.canvas = mlx_new_image(game.mlx, game.width, game.height);
	game.canvas_bytes = mlx_get_data_addr(game.canvas, &game.canvas_bpp, &game.canvas_line_size, &endian);
	game.canvas_bpp = game.canvas_bpp / 8;
	
	game.katana.current_i = 0;
	game.katana.count = 6;
	game.katana.next_frame_ts = 0;
	game.katana.pause_duration = 750;
	game.katana.frame_duration = 200;
	game.katana.sprites = malloc(sizeof(t_anim) * game.katana.count);
	load_image(&game.katana.sprites[0], "assets/katana/katana_new_1.xpm", game.mlx);
	load_image(&game.katana.sprites[1], "assets/katana/katana_new_2.xpm", game.mlx);
	load_image(&game.katana.sprites[2], "assets/katana/katana_new_4.xpm", game.mlx);
	load_image(&game.katana.sprites[3], "assets/katana/katana_new_3.xpm", game.mlx);
	load_image(&game.katana.sprites[4], "assets/katana/katana_new_4.xpm", game.mlx);
	load_image(&game.katana.sprites[5], "assets/katana/katana_new_2.xpm", game.mlx);

	load_image(&game.map.north, "assets/japan/north.xpm", game.mlx);
	load_image(&game.map.south, "assets/japan/south.xpm", game.mlx);
	load_image(&game.map.east, "assets/japan/east.xpm", game.mlx);
	load_image(&game.map.west, "assets/japan/west.xpm", game.mlx);
	load_image(&game.map.floor_img, "assets/japan/floor.xpm", game.mlx);
	load_image(&game.map.ceiling_img, "assets/japan/ceiling.xpm", game.mlx);
	//load_color(&game.map.ceiling_img, 0x00ff0000, game.mlx);
	load_image(&game.menu1_img, "assets/menu/menu1.xpm", game.mlx);
	load_image(&game.menu2_img, "assets/menu/menu2.xpm", game.mlx);
	load_image(&game.menuv_img, "assets/menu/menuv.xpm", game.mlx);
	game.display_menu = 3;
	mlx_hook(game.win, 17, 0, (void *)game_quit, &game);
	mlx_hook(game.win, 2, 1L << 0, key_pressed, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (1);
}
