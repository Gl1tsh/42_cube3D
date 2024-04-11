/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:56:10 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/04/11 10:33:40 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	free_minimap(t_game *game)
{
	free_image(&game->minimap.scroll, game->mlx);
	free_image(&game->minimap.image, game->mlx);
}

int	init_minimap(t_minimap *minimap, void *mlx)
{
	minimap->player_color = 0x00ffffff;
	minimap->floor_color = 0x00845b2a;
	minimap->wall_color = 0x004c3228;
	minimap->half_width = 10;
	minimap->half_height = 5;
	minimap->item_size = 10;
	if (load_image(&minimap->scroll, "assets/scroll.xpm", mlx) != 0)
		return (ERR_MINIMAP);
	return (create_image(&minimap->image,
			minimap->half_width * 2 * minimap->item_size,
			minimap->half_height * 2 * minimap->item_size, mlx));
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

void	draw_player(t_minimap *minimap, t_game *game)
{
	int	x;
	int	y;

	x = minimap->half_width * minimap->item_size;
	y = minimap->half_height * minimap->item_size;
	put_pixel(&minimap->image, x, y, minimap->player_color);
	put_pixel(&minimap->image, x, y - 1, minimap->player_color);
	put_pixel(&minimap->image, x, y + 1, minimap->player_color);
	put_pixel(&minimap->image, x - 1, y, minimap->player_color);
	put_pixel(&minimap->image, x + 1, y, minimap->player_color);
	mlx_put_image_to_window(game->mlx, game->win, minimap->scroll.img, 10, 10);
	mlx_put_image_to_window(game->mlx, game->win, minimap->image.img, 38, 38);
	mlx_put_image_to_window(game->mlx, game->win, minimap->scroll.img,
		minimap->half_width * 2 * minimap->item_size + 38, 10);
}

void	draw_minimap(t_minimap *minimap, t_game *game)
{
	int				x;
	int				y;
	int				x_offset;
	int				y_offset;
	double			dummy;

	x_offset = modf(game->player_x, &dummy) * minimap->item_size;
	y_offset = modf(game->player_y, &dummy) * minimap->item_size;
	x = -minimap->half_width - 1;
	while (++x <= minimap->half_width)
	{
		y = -minimap->half_height - 1;
		while (++y <= minimap->half_height)
			if (map_get_at(&game->map, x + game->player_x, y
					+ game->player_y) == '0')
				draw_square(minimap, (x + minimap->half_width)
					* minimap->item_size - x_offset, (y + minimap->half_height)
					* minimap->item_size - y_offset, minimap->floor_color);
		else
			draw_square(minimap, (x + minimap->half_width)
				* minimap->item_size - x_offset, (y + minimap->half_height)
				* minimap->item_size - y_offset, minimap->wall_color);
	}
	draw_player(minimap, game);
}
