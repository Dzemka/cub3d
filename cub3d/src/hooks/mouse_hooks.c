/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <olugash@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 07:25:11 by olugash           #+#    #+#             */
/*   Updated: 2022/11/18 07:26:09 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	vertical_view(int y, t_game *game)
{
	double	rotate_speed;

	rotate_speed = 50.0 / HEIGHT;
	if (y > HEIGHT / 2)
		game->pitch -= 400 * rotate_speed;
	if (game->pitch < -400)
		game->pitch = -400;
	if (y < HEIGHT / 2)
		game->pitch += 400 * rotate_speed;
	if (game->pitch > 400)
		game->pitch = 400;
}

static void	horizontal_view(int x, t_game *game)
{
	double	rotate_speed;
	double	old_dir_x;
	double	old_plane_x;

	rotate_speed = 0;
	if (x > WIDTH / 2)
		rotate_speed = 50.0 / WIDTH;
	if (x < WIDTH / 2)
		rotate_speed = -(50.0 / WIDTH);
	old_dir_x = game->player.dir.x;
	game->player.dir.x = game->player.dir.x * cos(rotate_speed)
		- game->player.dir.y * sin(rotate_speed);
	game->player.dir.y = old_dir_x * sin(rotate_speed)
		+ game->player.dir.y * cos(rotate_speed);
	old_plane_x = game->player.plane.x;
	game->player.plane.x = game->player.plane.x * cos(rotate_speed)
		- game->player.plane.y * sin(rotate_speed);
	game->player.plane.y = old_plane_x * sin(rotate_speed)
		+ game->player.plane.y * cos(rotate_speed);
}

int	mouse_press(int button, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	if (button == 1)
		game->player.attack = 1;
	return (0);
}

int	mouse_move(int x, int y, t_game *game)
{
	vertical_view(y, game);
	horizontal_view(x, game);
	mlx_mouse_move(game->window, WIDTH / 2, HEIGHT / 2);
	return (0);
}
