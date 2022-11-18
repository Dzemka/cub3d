/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minimap_frame.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <olugash@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 07:41:35 by olugash           #+#    #+#             */
/*   Updated: 2022/11/18 07:43:45 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	malloc_minimap_buffer(t_game *game, int size)
{
	int	y;

	game->minimap_frame_buffer = malloc(sizeof(int *) * (size + 1));
	if (!game->minimap_frame_buffer)
		game_exit("Malloc error");
	game->minimap_frame_buffer[size] = NULL;
	y = -1;
	while (++y < size)
	{
		game->minimap_frame_buffer[y] = malloc(sizeof(int *) * (size + 1));
		if (!game->minimap_frame_buffer[y])
			game_exit("Malloc error\n");
		game->minimap_frame_buffer[y][size] = '\0';
	}
}

void	fill_buffer(t_game *game, int radius, int size)
{
	int	x;
	int	y;
	int	r_square;
	int	r_x;
	int	r_y;

	r_square = radius * radius;
	y = -1;
	while (++y < size)
	{
		r_y = (y - radius) * (y - radius);
		x = -1;
		while (++x < size)
		{
			r_x = (x - radius) * (x - radius);
			if (r_x + r_y > r_square - r_square / 50 && r_x + r_y < r_square)
				game->minimap_frame_buffer[y][x] = 0xFF00FF;
			else if (r_x + r_y < 30)
				game->minimap_frame_buffer[y][x] = 0xFFFFFF;
			else if (r_x + r_y < r_square - r_square / 50)
				game->minimap_frame_buffer[y][x] = 0x1;
			else
				game->minimap_frame_buffer[y][x] = 16777216;
		}
	}
}

void	init_minimap_frame(t_game *game)
{
	int	radius;
	int	size;

	radius = sqrt((HEIGHT / 5) * (HEIGHT / 5) + (WIDTH / 5) + (WIDTH / 5));
	size = radius + radius;
	game->minimap_size = size;
	malloc_minimap_buffer(game, size);
	fill_buffer(game, radius, size);
}
