/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:36:16 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/03/06 18:06:32 by nagiorgi         ###   ########.fr       */
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
	map->celling_color = 0x00aaaaff; //bleu pale
	map->floor_color = 0x00608060; // vert gazon
	map->wall_color = 0x00ff00ff; // horrible
	return (0);
}

void	*draw_vertical_line(t_game *game, int x, int start_y, int end_y, unsigned int color)
{
	while (start_y < end_y)
	{
		*(unsigned int *)(game->canvas_bytes + (x * game->canvas_bpp) + (game->canvas_line_size * start_y)) = color;
		start_y++;
	}
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
	int		endian;

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
	game.canvas = mlx_new_image(game.mlx, game.width, game.height);
	game.canvas_bytes = mlx_get_data_addr(game.canvas, &game.canvas_bpp, &game.canvas_line_size, &endian);
	game.canvas_bpp = game.canvas_bpp / 8;
	draw_vertical_line(&game, game.width / 2, 0, game.height / 3, game.map.celling_color);
	draw_vertical_line(&game, game.width / 2, game.height / 3, game.height / 3 * 2, game.map.wall_color);
	draw_vertical_line(&game, game.width / 2, game.height / 3 * 2, game.height, game.map.floor_color);
	mlx_put_image_to_window(game.mlx, game.win, game.canvas, 0, 0);
	mlx_hook(game.win, 17, 0, (void *)game_quit, &game);
	mlx_key_hook(game.win, key_pressed, &game);
	mlx_loop(game.mlx);
	return (1);
}
