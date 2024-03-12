/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:27:16 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/03/12 18:48:46 by nagiorgi         ###   ########.fr       */
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

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

void	draw_vertical_line(t_game *game, t_coord *start,
	int end_y, unsigned int color)
{
	if (start->y < 0)
		start->y = 0;
	if (end_y > game->height)
		end_y = game->height;
	while (start->y < end_y)
	{
		*(unsigned int *)(game->canvas_bytes + (start->x * game->canvas_bpp)
				+ (game->canvas_line_size * start->y)) = color;
		start->y++;
	}
}

void	draw_wall(t_game *game, int x, t_ray *ray, t_image	*texture)
{
	double	delta_y;
	double	y;
	int		max_y;
	t_coord	tex_coord;
	t_coord	line_start;

	tex_coord.x = (int)(texture->width * (ray->x + ray->y)) % texture->width;
	delta_y = (double)(ray->wall_height * 2) / (double)(texture->height);
	y = game->height / 2 - ray->wall_height;
	max_y = game->height / 2 + ray->wall_height;
	tex_coord.y = 0;
	while (y < max_y)
	{
		line_start.x = x;
		line_start.y = y;
		draw_vertical_line(game, &line_start, y + delta_y,
			get_pixel(texture, tex_coord.x, tex_coord.y));
		y += delta_y;
		tex_coord.y++;
	}
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
	ray->distance = sqrt(pow(game->player_x - ray->x, 2.0)
			+ pow(game->player_y - ray->y, 2.0));
	ray->distance = ray->distance * cos(ray->angle - game->player_angle);
	ray->wall_height = (double)(game->height) / (1.5 * ray->distance);
}

t_image	*select_texture(t_game *game, t_ray *ray)
{
	if (map_get_at(&game->map, ray->x, ray->y - fabs(ray->sin)) == '0')
		return (&game->map.north);
	else if (map_get_at(&game->map, ray->x, ray->y + fabs(ray->sin)) == '0')
		return (&game->map.south);
	else if (map_get_at(&game->map, ray->x + fabs(ray->cos), ray->y) == '0')
		return (&game->map.east);
	else if (map_get_at(&game->map, ray->x - fabs(ray->cos), ray->y) == '0')
		return (&game->map.west);
	return (&game->map.north);
}

void	draw_rays(t_game *game)
{
	t_ray	ray;
	t_coord	coord;
	int		x;
	t_image	*texture;

	ray.angle = game->player_angle - game->half_fov;
	x = 0;
	while (x < game->width)
	{
		compute_ray(game, &ray);
		texture = select_texture(game, &ray);
		coord.x = x;
		coord.y = 0;
		draw_vertical_line(game, &coord, game->height / 2 - ray.wall_height,
			game->map.celling_color);
		draw_wall(game, x, &ray, texture);
		coord.x = x;
		coord.y = game->height / 2 + ray.wall_height;
		draw_vertical_line(game, &coord, game->height, game->map.floor_color);
		ray.angle += game->angle_increment;
		x++;
	}
}
