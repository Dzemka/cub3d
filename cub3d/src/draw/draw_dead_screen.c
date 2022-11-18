/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_dead_screen.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <olugash@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 05:41:23 by olugash           #+#    #+#             */
/*   Updated: 2022/11/18 05:42:18 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	draw_dead_screen(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			ft_pixel_put(&game->img, x, y, 0x0);
	}
	mlx_put_image_to_window(game->mlx, game->window, game->img.img, 0, 0);
	mlx_string_put(game->mlx, game->window, WIDTH / 2, HEIGHT / 2, 0xFF0000,
		"You are dead");
	mlx_string_put(game->mlx, game->window, WIDTH / 2 - 20, HEIGHT / 2 + 50,
		0x00FF00, "Press R to restart");
	return (0);
}
