/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <olugash@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 07:23:32 by olugash           #+#    #+#             */
/*   Updated: 2022/11/18 07:24:58 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	horizontal_view(int keycode, t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rotate_speed;

	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
	{
		rotate_speed = 0.1;
		if (keycode == KEY_RIGHT)
			rotate_speed *= -1;
		old_dir_x = game->player.dir.x;
		game->player.dir.x = game->player.dir.x * cos(-rotate_speed)
			- game->player.dir.y * sin(-rotate_speed);
		game->player.dir.y = old_dir_x * sin(-rotate_speed)
			+ game->player.dir.y * cos(-rotate_speed);
		old_plane_x = game->player.plane.x;
		game->player.plane.x = game->player.plane.x * cos(-rotate_speed)
			- game->player.plane.y * sin(-rotate_speed);
		game->player.plane.y = old_plane_x * sin(-rotate_speed)
			+ game->player.plane.y * cos(-rotate_speed);
	}
}

static void	vertical_view(int keycode, t_game *game)
{
	if (keycode == KEY_DOWN)
	{
		game->pitch -= 400 * PLAYER_MOVE_SPEED;
		if (game->pitch < -400)
			game->pitch = -400;
	}
	if (keycode == KEY_UP)
	{
		game->pitch += 400 * PLAYER_MOVE_SPEED;
		if (game->pitch > 400)
			game->pitch = 400;
	}
}

int	key_hooks(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		exit(1);
	if (keycode == KEY_R)
		get_start(game);
	if (keycode == KEY_F)
		game->player.action = 1;
	if (keycode == KEY_W || keycode == KEY_A
		|| keycode == KEY_D || keycode == KEY_S)
		player_move(keycode, game);
	if (keycode == KEY_DOWN || keycode == KEY_UP)
		vertical_view(keycode, game);
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		horizontal_view(keycode, game);
	return (0);
}
