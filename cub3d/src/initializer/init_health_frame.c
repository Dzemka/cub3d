/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_health_frame.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <olugash@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 07:38:59 by olugash           #+#    #+#             */
/*   Updated: 2022/11/18 07:40:48 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	malloc_frame(t_game *game, int size_x, int size_y)
{
	int	y;

	game->health_frame_buffer = malloc(sizeof(int *) * (size_y + 1));
	if (!game->health_frame_buffer)
		game_exit("Malloc error");
	game->health_frame_buffer[size_y] = NULL;
	y = -1;
	while (++y < size_y)
	{
		game->health_frame_buffer[y] = malloc(sizeof(int) * (size_x + 1));
		if (!game->health_frame_buffer[y])
			game_exit("Malloc error\n");
		game->health_frame_buffer[y][size_x] = '\0';
	}
}

static void	fill_buffer(t_game *game, int size_x, int size_y)
{
	int	y;
	int	x;

	y = game->coord_start_hp.y - 1;
	while (++y < size_y)
	{
		x = game->coord_start_hp.x - 1;
		while (++x < size_x)
		{
			if (((y == game->coord_start_hp.y || y == size_y - 1)
					&& x >= game->coord_start_hp.x
					&& x < size_x) || ((x == game->coord_start_hp.x
						|| x == size_x - 1) && y >= game->coord_start_hp.y
					&& y < size_y))
				game->health_frame_buffer[y][x] = 0xFF00FF;
			else if (y > game->coord_start_hp.y && y < size_y
				&& x > game->coord_start_hp.x && x < size_x)
				game->health_frame_buffer[y][x] = 0x1;
		}
	}
}

void	init_health_frame(t_game *game)
{
	int	height_frame;
	int	width_frame;
	int	size_y;
	int	size_x;

	fill_coord(HEIGHT - HEIGHT / 10, WIDTH / 15, &game->coord_start_hp);
	height_frame = HEIGHT / 30;
	width_frame = WIDTH / 5;
	size_y = (int)game->coord_start_hp.y + height_frame;
	size_x = (int)game->coord_start_hp.x + width_frame;
	malloc_frame(game, size_x, size_y);
	fill_buffer(game, size_x, size_y);
}
