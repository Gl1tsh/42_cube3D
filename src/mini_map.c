/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:56:10 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/03/26 18:12:38 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_minimap(t_minimap *minimap, void *mlx)
{
	minimap->player_color = 0x00ff0000;
	minimap->floor_color = 0x00608060;
	minimap->wall_color = 0x00804000;
	minimap->half_width = 10;
	minimap->half_height = 5;
	minimap->item_size = 10;
	create_image(&minimap->image, minimap->half_width * 2 * minimap->item_size,
		minimap->half_height * 2 * minimap->item_size, mlx);
}

void	draw_square(t_minimap *minimap, int x, int y, unsigned int color)
{
	int	x_index;
	int	y_index;

	x_index = x;
	if (x < 0 || x >= (minimap->image.width - minimap->item_size))
		return ;
	if (y < 0 || y >= (minimap->image.height - minimap->item_size))
		return ;
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
	double			dummy;

	x_offset = modf(game->player_x, &dummy) * minimap->item_size;
	y_offset = modf(game->player_y, &dummy) * minimap->item_size;
	x = -minimap->half_width;
	while (x <= minimap->half_width)
	{
		y = -minimap->half_height;
		while (y <= minimap->half_height)
		{
			if (map_get_at(&game->map, x + game->player_x, y + game->player_y) == '0')
				color = minimap->floor_color;
			else
				color = minimap->wall_color;
			draw_square(minimap, (x + minimap->half_width) * minimap->item_size - x_offset, (y + minimap->half_height) * minimap->item_size - y_offset, color);
			y++;
		}
		x++;
	}
	put_pixel(&minimap->image, (minimap->half_width) * minimap->item_size, (minimap->half_height) * minimap->item_size, minimap->player_color);
	put_pixel(&minimap->image, (minimap->half_width) * minimap->item_size, (minimap->half_height) * minimap->item_size + 1, minimap->player_color);
	put_pixel(&minimap->image, (minimap->half_width) * minimap->item_size, (minimap->half_height) * minimap->item_size - 1, minimap->player_color);
	put_pixel(&minimap->image, (minimap->half_width) * minimap->item_size + 1, (minimap->half_height) * minimap->item_size, minimap->player_color);
	put_pixel(&minimap->image, (minimap->half_width) * minimap->item_size - 1, (minimap->half_height) * minimap->item_size, minimap->player_color);
	mlx_put_image_to_window(game->mlx, game->win, minimap->image.img, 10, 10);
}
