/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:36:49 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/03/18 17:37:46 by nagiorgi         ###   ########.fr       */
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
//bonus
# include <string.h>
# include <sys/errno.h>
# include <math.h>

# define KEY_W 13
# define KEY_S 1
# define KEY_A 0
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_ESC 53
# define KEY_ENTER 36

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

typedef struct s_anim
{
	int			count;
	int			pause_duration;
	int			frame_duration;
	int			current_i;
	long		next_frame_ts;
	t_image		*current;
	t_image		*sprites;

}	t_anim;

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
	t_image			ceiling_img;
	t_image			floor_img;
	t_anim			north;
	t_anim			south;
	t_anim			east;
	t_anim			west;
}	t_map;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_map		map;
	int			width;
	int			height;
	void		*canvas;
	char		*canvas_bytes;
	int			canvas_bpp;
	int			canvas_line_size;
	double		player_x;
	double		player_y;
	double		player_angle;
	double		player_angle_delta;
	double		player_speed;
	double		half_fov;
	double		precision;
	double		angle_increment;
	long		next_frame_ts;
	long		frame_delay;
	char		keys[256];
	int			display_menu;
	t_image		menu1_img;
	t_image		menu2_img;
	t_image		menuv_img;
	t_anim		katana;
}	t_game;

typedef struct s_ray
{
	double	angle;
	double	x;
	double	y;
	double	cos;
	double	sin;
	double	distance;
	int		wall_height;
	double	direction_cos;
	double	direction_sin;
	double	fisheye_corr;
}	t_ray;

// free or quit game
void			game_quit_error(t_game *game, const char *error_msg);
void			game_quit(t_game *game);
void			game_free(t_game *game);

// utils
long			get_timestamp_ms(void);
void			put_pixel(t_game *game, int x, int y, unsigned int color);
unsigned int	get_pixel(t_image *image, int x, int y);

// map
int				load_map(t_map *map, char *path_name);
char			map_get_at(t_map *map, int x, int y);

// draw
void			draw_rays(t_game *game);
void			draw_floor(t_game *game, int x, t_ray *ray);
void			draw_ceiling(t_game *game, int x, t_ray *ray);
void			draw_wall(t_game *game, int x, t_ray *ray, t_image *texture);

// game
int				game_loop(t_game *game);
int				menu_loop(t_game *game, long now);

// player
void			rotate_player(t_game *game, double sign);
void			move_player(t_game *game, double angle_delta);
void			update_player(t_game *game);

// anim
void			update_anim(t_anim *anim, long now);
void			load_anim(t_anim *anim, int pause_duration, int frame_duration,
					char **filenames, void *mlx);

// autre
int				load_image(t_image *image, char *filename, void *mlx);

#endif
