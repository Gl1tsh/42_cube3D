/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 15:54:13 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/04/14 15:48:39 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static char	*g_error_msgs[] = {
	"no error",
	"global error",
	"North texture loading failure",
	"South texture loading failure",
	"East texture loading failure",
	"West texture loading failure",
	"Floor texture loading failure",
	"Ceiling texture loading failure",
	"HUD texture loading failure",
	"File extension",
	"File empty",
	"Map allocation",
	"Map size too small",
	"Map borders",
	"Player missing",
	"Invalid char",
	"Empty line in map",
	"MLX error",
	"Allocation error",
	"Minimap error",
	"Menu error",
	"Missing informations on files",
	"Bad file",
};

void	game_free(t_game *game)
{
	if (game->win != NULL)
		mlx_destroy_window(game->mlx, game->win);
	free_map(game);
	free_minimap(game);
	free_menu(game);
}

void	game_quit(t_game *game)
{
	if (system("pgrep afplay > /dev/null") == 0)
		system("killall afplay");
	game_free(game);
	exit(0);
}

void	game_quit_error(t_game *game, int error_number)
{
	if (system("pgrep afplay > /dev/null") == 0)
		system("killall afplay");
	game_free(game);
	if (error_number < 0 || error_number > ERR_MAX)
		printf("Error\nGlobal Error %d\n", error_number);
	else
		printf("Error\n%s\n", g_error_msgs[error_number]);
	exit(1);
}

void	quit_if_error(t_game *game, int error_number)
{
	if (error_number > 0)
		game_quit_error(game, error_number);
}
