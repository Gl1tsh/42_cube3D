/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:56:10 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/03/23 21:26:59 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_minimap(t_minimap *minimap, void *mlx)
{
	minimap->player_color = 0x00aaaaff;
	minimap->floor_color = 0x00608060;
	minimap->wall_color = 0x00804000;
	minimap->width = 18;
	minimap->height = 10;
	minimap->item_size = 10;
	create_image(&minimap->image, minimap->width * minimap->item_size,
		minimap->height * minimap->item_size, mlx);
}

void	draw_square(t_minimap *minimap, int x, int y, unsigned int color)
{
	int	x_index;
	int	y_index;

	x_index = x;
	while (x_index < (x + minimap->item_size))
	{
		y_index = y;
		while (y_index < (y + minimap->item_size))
		{
			put_pixel(&minimap->image, x_index, y_index, color);
			y_index++;
		}
		x_index++;
	}
}

void	draw_minimap(t_minimap *minimap, t_game *game)
{
	int				x;
	int				y;
	int				x_offset;
	int				y_offset;
	unsigned int	color;

	x_offset = game->player_x - (minimap->width / 2);
	y_offset = game->player_y - (minimap->height / 2);
	x = 0;
	while (x < minimap->width)
	{
		y = 0;
		while (y < minimap->height)
		{
			if (map_get_at(&game->map, x + x_offset, y + y_offset) == '0')
				color = minimap->floor_color;
			else
				color = minimap->wall_color;
			draw_square(minimap, x * minimap->item_size, y * minimap->item_size, color);
			y++;
		}
		x++;
	}
	draw_square(minimap, (minimap->width / 2) * minimap->item_size, (minimap->height / 2) * minimap->item_size, minimap->player_color);
	mlx_put_image_to_window(game->mlx, game->win, minimap->image.img, 10, 10);
}
