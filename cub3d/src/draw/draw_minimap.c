/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <olugash@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 05:45:20 by olugash           #+#    #+#             */
/*   Updated: 2022/11/18 08:29:14 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	select_color(t_game *game, ssize_t map_x, ssize_t map_y)
{
	if (map_y >= 0 && map_y < (ssize_t)game->map->height
		&& map_x >= 0 && map_x < (ssize_t)game->map->width)
	{
		if (game->map->map_grid[(int)map_y][(int)map_x] == '-'
			|| game->map->map_grid[(int)map_y][(int)map_x] == ' ')
			return (0x1);
		else if (game->map->map_grid[(int)map_y][(int)map_x] == '1')
			return (0x480607);
		else if (game->map->map_grid[(int)map_y][(int)map_x] == '0')
			return (0x4E5754);
		else if (ft_strchr("6789", game->map->map_grid[(int)map_y][(int)map_x]))
			return (0xFF0000);
		else if (ft_strchr("2345", game->map->map_grid[(int)map_y][(int)map_x]))
			return (0x00FF00);
		else if (game->map->map_grid[(int)map_y][(int)map_x] == 'D')
			return (0x0FFFF0);
	}
	return (0x1);
}

static void	fill_buffer(t_game *game, double step, double map_x, double map_y)
{
	int		x;
	int		y;
	double	start;

	start = map_x;
	y = -1;
	while (game->minimap_frame_buffer[++y])
	{
		x = -1;
		map_x = start;
		while (game->minimap_frame_buffer[y][++x])
		{
			if (game->minimap_frame_buffer[y][x] != 16777216)
			{
				if (game->minimap_frame_buffer[y][x] == 0x1)
					game->buffer[y][x] = select_color(game, map_x, map_y);
				else
					game->buffer[y][x] = game->minimap_frame_buffer[y][x];
			}
			map_x += step;
		}
		map_y += step;
	}
}

void	draw_minimap(t_game *game)
{
	double	step;
	double	map_x;
	double	map_y;

	map_x = (double)game->player.pos.x - RANGE_MINIMAP / 2.0;
	map_y = (double)game->player.pos.y - RANGE_MINIMAP / 2.0;
	step = (double)RANGE_MINIMAP / (double)game->minimap_size;
	fill_buffer(game, step, map_x, map_y);
}
