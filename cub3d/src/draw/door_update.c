/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <olugash@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 05:34:50 by olugash           #+#    #+#             */
/*   Updated: 2022/11/18 05:40:50 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	time_to_close(t_game *game)
{
	size_t	i;
	size_t	j;

	while (++i < game->map->height)
	{
		j = -1;
		while (++j < game->map->width)
		{
			if (game->map->door_map[i][j].open == 1)
			{
				game->map->door_map[i][j].frame++;
				if (game->map->door_map[i][j].frame % SPEED_DOOR_CLOSING == 0)
				{
					game->map->door_map[i][j].open = -1;
				}
				if (game->map->door_map[i][j].frame == 100)
					game->map->door_map[i][j].frame = 0;
			}
		}
	}
}

void	door_update(t_game *game)
{
	int		y;
	int		x;
	double	dir_x;
	double	dir_y;

	if (game->player.action == 1)
	{
		y = game->player.pos.y;
		x = game->player.pos.x;
		dir_x = game->player.dir.x;
		dir_y = game->player.dir.y;
		game->player.action = 0;
		if (game->map->door_map[y][x + (int)ceil(dir_x)].open != 0)
			game->map->door_map[y][x + (int)ceil(dir_x)].open *= -1;
		else if (game->map->door_map[y][x + (int)floor(dir_x)].open != 0)
			game->map->door_map[y][x + (int)floor(dir_x)].open *= -1;
		else if (game->map->door_map[y + (int)ceil(dir_y)][x].open != 0)
			game->map->door_map[y + (int)ceil(dir_y)][x].open *= -1;
		else if (game->map->door_map[y + (int)floor(dir_y)][x].open != 0)
			game->map->door_map[y + (int)floor(dir_y)][x].open *= -1;
	}
	time_to_close(game);
}
