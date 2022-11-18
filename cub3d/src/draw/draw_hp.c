/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <olugash@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 05:42:23 by olugash           #+#    #+#             */
/*   Updated: 2022/11/18 05:45:09 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_hp(t_game *game)
{
	int	x;
	int	y;
	int	width_frame;
	int	scale;

	width_frame = WIDTH / 5;
	scale = width_frame * game->player.health / 100;
	y = game->coord_start_hp.y - 1;
	while (game->health_frame_buffer[++y])
	{
		x = game->coord_start_hp.x - 1;
		while (game->health_frame_buffer[y][++x])
		{
			game->buffer[y][x] = 0xFF0000;
			game->buffer[y][x] = game->health_frame_buffer[y][x];
			if (game->health_frame_buffer[y][x] == 0x1)
			{
				if (x < game->coord_start_hp.x + scale)
					game->buffer[y][x] = 0xFF0000;
			}
		}
	}
}
