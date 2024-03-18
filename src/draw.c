/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:27:16 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/03/18 17:40:06 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	compute_ray(t_game *game, t_ray *ray)
{
	char	wall;

	ray->x = game->player_x;
	ray->y = game->player_y;
	ray->cos = cos(ray->angle) / game->precision;
	ray->sin = sin(ray->angle) / game->precision;
	ray->direction_cos = cos(ray->angle);
	ray->direction_sin = sin(ray->angle);
	ray->fisheye_corr = cos(ray->angle - game->player_angle);
	wall = '0';
	while (wall == '0')
	{
		ray->x += ray->cos;
		ray->y += ray->sin;
		wall = map_get_at(&game->map, ray->x, ray->y);
	}
	ray->distance = sqrt(pow(game->player_x - ray->x, 2.0)
			+ pow(game->player_y - ray->y, 2.0));
	ray->distance = ray->distance * ray->fisheye_corr;
	ray->wall_height = (double)(game->height) / (1.5 * ray->distance);
}

t_image	*select_texture(t_game *game, t_ray *ray)
{
	if (map_get_at(&game->map, ray->x, ray->y - fabs(ray->sin)) == '0')
		return (game->map.north.current);
	else if (map_get_at(&game->map, ray->x, ray->y + fabs(ray->sin)) == '0')
		return (game->map.south.current);
	else if (map_get_at(&game->map, ray->x + fabs(ray->cos), ray->y) == '0')
		return (game->map.east.current);
	else if (map_get_at(&game->map, ray->x - fabs(ray->cos), ray->y) == '0')
		return (game->map.west.current);
	return (game->map.north.current);
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
		texture = select_texture(game, &ray);
		draw_ceiling(game, x, &ray);
		draw_wall(game, x, &ray, texture);
		draw_floor(game, x, &ray);
		ray.angle += game->angle_increment;
		x++;
	}
}
