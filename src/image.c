/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:09:15 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/04/12 00:39:47 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	my_atoi(const char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	return (result);
}

void	free_image(t_image *image, void *mlx)
{
	if (image->img != NULL)
		mlx_destroy_image(mlx, image->img);
}

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

int	parse_color(char *str, unsigned int *color)
{
	char	**parts;
	int		r;
	int		g;
	int		b;

	parts = ft_split(str, ',');
	if (parts[0] == NULL)
		return (!free_array(parts, 0));
	r = my_atoi(parts[0]);
	if (parts[1] == NULL)
		return (!free_array(parts, 0));
	g = my_atoi(parts[1]);
	if (parts[2] == NULL)
		return (!free_array(parts, 0));
	b = my_atoi(parts[2]);
	if (parts[3] != NULL)
		return (!free_array(parts, 0));
	free_array(parts, 0);
	if (r > 255 || g > 255 || b > 255 || r < 0 || g < 0 || b < 0)
		return (1);
	*color = r << 16 | g << 8 | b;
	return (0);
}

int	load_image(t_image *image, char *filename, void *mlx)
{
	int				endian;
	unsigned int	color;

	if (parse_color(filename, &color) == 0)
	{
		if (create_image(image, 1, 1, mlx) != 0)
			return (1);
		put_pixel(image, 0, 0, color);
		return (0);
	}
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
