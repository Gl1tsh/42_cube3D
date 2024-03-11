/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:36:49 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/03/11 18:22:53 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

/* Librairies */
# include "mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/errno.h>
# include <math.h>

# define KEY_W 13
# define KEY_S 1
# define KEY_A 0
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_ESC 53

# define FPS 60

typedef struct s_image
{
	void	*img;
	int		height;
	int		width;
	char	*bytes;
	int		bpp;
	int		line_size;
}	t_image;

typedef struct s_map
{
	char			*bytes;
	int				width;
	int				height;
	int				player_x;
	int				player_y;
	unsigned int	celling_color;
	unsigned int	floor_color;
	unsigned int	wall_color;
	t_image			north;
	t_image			south;
	t_image			east;
	t_image			west;
}	t_map;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_map	map;
	int		width;
	int		height;
	void	*canvas;
	char	*canvas_bytes;
	int		canvas_bpp;
	int		canvas_line_size;
	double	player_x;
	double	player_y;
	double	player_angle;
	double	player_angle_delta;
	double	player_speed;
	double	half_fov;
	double	precision;
	double	angle_increment;
	long	next_frame_ts;
	long	frame_delay;
	char	keys[256];
}	t_game;

// free or quit game
void	game_quit_error(t_game *game, const char *error_msg);
void	game_quit(t_game *game);
void	game_free(t_game *game);

#endif
