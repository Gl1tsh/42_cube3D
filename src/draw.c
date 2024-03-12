/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:27:16 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/03/12 17:46:13 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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

void	draw_ceiling(t_game *game, int x, int wall_height)
{
	draw_vertical_line(game, x, 0, game->height / 2 - wall_height, game->map.celling_color);
}

void	draw_wall(t_game *game, int x, int wall_height, double ray_x, double ray_y, t_image	*texture)
{
	double	delta_y;
	double	y;
	int		max_y;
	int		texture_y;
	int		texture_x;

	texture_x = (int)(texture->width * (ray_x + ray_y)) % texture->width;
	delta_y = (double)(wall_height * 2) / (double)(texture->height);
	y = game->height / 2 - wall_height;
	max_y = game->height / 2 + wall_height;
	texture_y = 0;
	while (y < max_y)
	{
		draw_vertical_line(game, x, y, y + delta_y, get_pixel(texture, texture_x, texture_y));
		y += delta_y;
		texture_y++;
	}
}

void	draw_floor(t_game *game, int x, int wall_height)
{
	draw_vertical_line(game, x, game->height / 2 + wall_height, game->height, game->map.floor_color);
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
	t_image	*texture;

	ray_angle = game->player_angle - game->half_fov;
	x = 0;
	while (x < game->width)
	{
		ray_x = game->player_x;
		ray_y = game->player_y;
		ray_cos = cos(ray_angle) / game->precision;
		ray_sin = sin(ray_angle) / game->precision;
		wall = '0';
		while (wall == '0')
		{
			ray_x += ray_cos;
			ray_y += ray_sin;
			wall = map_get_at(&game->map, ray_x, ray_y);
		}
		distance = sqrt(pow(game->player_x - ray_x, 2.0) + pow(game->player_y - ray_y, 2.0));
		distance = distance * cos(ray_angle - game->player_angle);
		wall_height = (double)(game->height) / (1.5 * distance);
		texture = &game->map.north;
		if (map_get_at(&game->map, ray_x, ray_y - fabs(ray_sin)) == '0')
			texture = &game->map.north;
		else if (map_get_at(&game->map, ray_x, ray_y + fabs(ray_sin)) == '0')
			texture = &game->map.south;
		else if (map_get_at(&game->map, ray_x + fabs(ray_cos), ray_y) == '0')
			texture = &game->map.east;
		else if (map_get_at(&game->map, ray_x - fabs(ray_cos), ray_y) == '0')
			texture = &game->map.west;
		draw_ceiling(game, x, wall_height);
		draw_wall(game, x, wall_height, ray_x, ray_y, texture);
		draw_floor(game, x, wall_height);
		ray_angle += game->angle_increment;
		x++;
	}
}
