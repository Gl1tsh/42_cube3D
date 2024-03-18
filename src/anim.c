/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:45:26 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/03/18 17:48:57 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	update_anim(t_anim *anim, long now)
{
	if (now > anim->next_frame_ts)
	{
		if (anim->current_i == anim->count - 1)
		{
			anim->next_frame_ts = now + anim->pause_duration
				+ anim->frame_duration;
			anim->current_i = 0;
		}
		else
		{
			anim->current_i++;
			anim->next_frame_ts = now + anim->frame_duration;
		}
		anim->current = &anim->sprites[anim->current_i];
	}
}

void	load_anim(t_anim *anim, int pause_duration, int frame_duration,
	char **filenames, void *mlx)
{
	int	i;

	anim->current_i = 0;
	anim->next_frame_ts = 0;
	anim->pause_duration = pause_duration;
	anim->frame_duration = frame_duration;
	anim->count = 0;
	while (filenames[anim->count] != NULL)
		anim->count++;
	anim->sprites = malloc(sizeof(t_anim) * anim->count);
	i = 0;
	while (filenames[i] != NULL)
	{
		load_image(&anim->sprites[i], filenames[i], mlx);
		i++;
	}
	anim->current = &anim->sprites[0];
}
