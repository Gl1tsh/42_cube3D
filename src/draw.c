/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:27:16 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/03/12 18:09:01 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

typedef struct s_ray
{
	double	angle;
	double	x;
	double	y;
	double	cos;
	double	sin;
	double	distance;
	int		wall_height;
}	t_ray;

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

void	compute_ray(t_game *game, t_ray *ray)
{
	char	wall;

	ray->x = game->player_x;
	ray->y = game->player_y;
	ray->cos = cos(ray->angle) / game->precision;
	ray->sin = sin(ray->angle) / game->precision;
	wall = '0';
	while (wall == '0')
	{
		ray->x += ray->cos;
		ray->y += ray->sin;
		wall = map_get_at(&game->map, ray->x, ray->y);
	}
	ray->distance = sqrt(pow(game->player_x - ray->x, 2.0) + pow(game->player_y - ray->y, 2.0));
	ray->distance = ray->distance * cos(ray->angle - game->player_angle);
	ray->wall_height = (double)(game->height) / (1.5 * ray->distance);
}

void	draw_rays(t_game *game)
{
	t_ray	ray;
	int		x;
	t_image	*texture;

	ray.angle = game->player_angle - game->half_fov;
	x = 0;
	while (x < game->width)
	{
		compute_ray(game, &ray);
		texture = &game->map.north;
		if (map_get_at(&game->map, ray.x, ray.y - fabs(ray.sin)) == '0')
			texture = &game->map.north;
		else if (map_get_at(&game->map, ray.x, ray.y + fabs(ray.sin)) == '0')
			texture = &game->map.south;
		else if (map_get_at(&game->map, ray.x + fabs(ray.cos), ray.y) == '0')
			texture = &game->map.east;
		else if (map_get_at(&game->map, ray.x - fabs(ray.cos), ray.y) == '0')
			texture = &game->map.west;
		draw_ceiling(game, x, ray.wall_height);
		draw_wall(game, x, ray.wall_height, ray.x, ray.y, texture);
		draw_floor(game, x, ray.wall_height);
		ray.angle += game->angle_increment;
		x++;
	}
}
