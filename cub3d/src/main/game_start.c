/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <olugash@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 07:46:43 by olugash           #+#    #+#             */
/*   Updated: 2022/11/18 07:47:41 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	ft_pixel_put(t_data_img *data, int x, int y, int color)
{
	*(int *)(data->addr + (y * data->line_length + x
				* (data->bpp / 8))) = color;
}

int	draw_game(t_game *game)
{
	int	x;
	int	y;

	draw_basic(game);
	draw_walls(game);
	draw_sprites(game);
	draw_weapon(game);
	draw_minimap(game);
	draw_hp(game);
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			ft_pixel_put(&game->img, x, y, game->buffer[y][x]);
	}
	mlx_put_image_to_window(game->mlx, game->window, game->img.img, 0, 0);
	return (0);
}

int	game_start(t_game *game)
{
	game->funct(game);
	return (0);
}
