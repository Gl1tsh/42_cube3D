/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:36:16 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/03/06 19:24:40 by nagiorgi         ###   ########.fr       */
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
	map->wall_color = 0x00804000; // horrible
	return (0);
}

void	draw_vertical_line(t_game *game, int x, int start_y, int end_y, unsigned int color)
{
	if (start_y < 0)
		start_y = 0;
	if (end_y > game->height)
		end_y = game->height;
	while (start_y < end_y)
	{
		*(unsigned int *)(game->canvas_bytes + (x * game->canvas_bpp) + (game->canvas_line_size * start_y)) = color;
		start_y++;
	}
}

void	draw_rays(t_game *game)
{
	int		x;
	double	ray_angle;
	double	ray_x;
	double	ray_y;
	double	ray_cos;
	double	ray_sin;
	double	distance;
	int		wall_height;
	char	wall;

	ray_angle = game->player_angle - game->half_fov;

	x = 0;
	while (x < game->width)
	{
		ray_x = game->map.player_x;
		ray_y = game->map.player_y;
		ray_cos = cos(ray_angle) / game->precision;
		ray_sin = sin(ray_angle) / game->precision;
		wall = '0';
		while (wall == '0')
		{
			ray_x += ray_cos;
			ray_y += ray_sin;
			wall = game->map.bytes[(int)(ray_y * game->map.width + ray_x)];
		}
		distance = sqrt(pow(game->player_x  - ray_x, 2) + pow(game->player_y - ray_y, 2));
		wall_height = (double)(game->height / 2) / distance;
		draw_vertical_line(game, x, 0, game->height / 2 - wall_height, game->map.celling_color);
		draw_vertical_line(game, x, game->height / 2 - wall_height, game->height / 2 + wall_height, game->map.wall_color);
		draw_vertical_line(game, x, game->height / 2 + wall_height, game->height, game->map.floor_color);
		ray_angle += game->angle_increment;
		x++;
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
	draw_rays(game);
	mlx_put_image_to_window(game->mlx, game->win, game->canvas, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;
	int		endian;

	game.precision = 128.0;
	game.half_fov = M_PI_2 / 3.0;
	game.player_angle = M_PI_2 / 6.2;
	game.width = 1024;
	game.height = 600;
	game.angle_increment = 2 * game.half_fov / game.width;
	if (load_map(&game.map, argv[1]) != 0)
		game_quit_error(&game, "erreur de map");
	game.player_x = game.map.player_x;
	game.player_y = game.map.player_y;
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
	mlx_hook(game.win, 17, 0, (void *)game_quit, &game);
	mlx_key_hook(game.win, key_pressed, &game);
	mlx_loop(game.mlx);
	return (1);
}
