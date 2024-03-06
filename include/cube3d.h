/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:36:49 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/03/06 17:24:45 by nagiorgi         ###   ########.fr       */
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

# define KEY_W 13
# define KEY_S 1
# define KEY_A 0
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_ESC 53

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
}	t_game;

// free or quit game
void	game_quit_error(t_game *game, const char *error_msg);
void	game_quit(t_game *game);
void	game_free(t_game *game);

#endif
