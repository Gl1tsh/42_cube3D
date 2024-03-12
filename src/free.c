/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 15:54:13 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/03/12 17:45:08 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	game_free(t_game *game)
{
	if (game->win != NULL)
		mlx_destroy_window(game->mlx, game->win);
}

void	game_quit(t_game *game)
{
	game_free(game);
	exit(0);
}

void	game_quit_error(t_game *game, const char *error_msg)
{
	game_free(game);
	printf("Error: %s\n", error_msg);
	exit(1);
}
