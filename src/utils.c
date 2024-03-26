/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:35:00 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/03/26 20:54:37 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <sys/time.h>

long	get_timestamp_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	put_pixel(t_image *image, int x, int y, unsigned int color)
{
	if (y < 0)
		y = 0;
	if (y > image->height)
		y = image->height;
	*(unsigned int *)(image->bytes + (x * image->bpp)
			+ (image->line_size * y)) = color;
}

unsigned int	get_pixel(t_image *image, int x, int y)
{
	return (*(unsigned int *)(image->bytes + (x * image->bpp)
		+ (image->line_size * y)));
}

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_strchr(WHITESPACE_CHARSET, line[i]) == NULL)
			return (0);
		i++;
	}
	return (1);
}
