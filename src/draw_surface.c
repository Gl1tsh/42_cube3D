/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_surface.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 19:48:36 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/03/26 21:37:16 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

void	draw_vertical_line(t_image *image, t_coord *start,
	int end_y, unsigned int color)
{
	if (start->y < 0)
		start->y = 0;
	if (end_y > image->height)
		end_y = image->height;
	while (start->y < end_y)
	{
		*(unsigned int *)(image->bytes + (start->x * image->bpp)
				+ (image->line_size * start->y)) = color;
		start->y++;
	}
}

void	draw_floor(t_game *game, int x, t_ray *ray)
{
	int		y;
	double	distance;
	double	tile_x;
	double	tile_y;
	t_coord	texture;

	y = game->height / 2 + ray->wall_height;
	while (y < game->height)
	{
		distance = (double)(game->height) / (double)(2 * y - game->height);
		distance = distance / ray->fisheye_corr;
		distance *= 1.296875;
		tile_x = game->player_x + distance * ray->direction_cos;
		tile_y = game->player_y + distance * ray->direction_sin;
		texture.x = (int)(tile_x * game->map.floor.current->width)
			% game->map.floor.current->width;
		texture.y = (int)(tile_y * game->map.floor.current->height)
			% game->map.floor.current->height;
		put_pixel(&game->canvas, x, y,
			get_pixel(game->map.floor.current, texture.x, texture.y));
		y++;
	}
}

void	draw_ceiling(t_game *game, int x, t_ray *ray)
{
	int		y;
	double	distance;
	double	tile_x;
	double	tile_y;
	t_coord	texture;

	y = game->height / 2 - ray->wall_height;
	while (y >= 0)
	{
		distance = (double)(game->height) / (double)(game->height - 2 * y);
		distance = distance / ray->fisheye_corr;
		distance *= 1.296875;
		tile_x = game->player_x + distance * ray->direction_cos;
		tile_y = game->player_y + distance * ray->direction_sin;
		texture.x = (int)(tile_x * game->map.ceiling.current->width)
			% game->map.ceiling.current->width;
		texture.y = (int)(tile_y * game->map.ceiling.current->height)
			% game->map.ceiling.current->height;
		put_pixel(&game->canvas, x, y,
			get_pixel(game->map.ceiling.current, texture.x, texture.y));
		y--;
	}
}

void	draw_wall(t_game *game, int x, t_ray *ray, t_image *texture)
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
		draw_vertical_line(&game->canvas, &line_start, y + delta_y,
			get_pixel(texture, tex_coord.x, tex_coord.y));
		y += delta_y;
		tex_coord.y++;
	}
}
