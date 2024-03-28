/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:09:15 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/03/28 13:11:05 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	create_image(t_image *image, int width, int height, void *mlx)
{
	int		endian;

	image->width = width;
	image->height = height;
	image->img = mlx_new_image(mlx, image->width, image->height);
	if (image->img == NULL)
		return (1);
	image->bytes = mlx_get_data_addr(image->img, &image->bpp,
			&image->line_size, &endian);
	if (image->bytes == NULL)
		return (1);
	image->bpp = image->bpp / 8;
	return (0);
}

int	load_image(t_image *image, char *filename, void *mlx)
{
	int		endian;

	image->img = mlx_xpm_file_to_image(mlx, filename, &image->width,
			&image->height);
	if (image->img == NULL)
		return (1);
	image->bytes = mlx_get_data_addr(image->img, &image->bpp,
			&image->line_size, &endian);
	if (image->bytes == NULL)
		return (1);
	image->bpp = image->bpp / 8;
	return (0);
}

void	free_image(t_image *image, void *mlx)
{
	mlx_destroy_image(mlx, image->img);
}
