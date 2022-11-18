/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <olugash@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 07:26:18 by olugash           #+#    #+#             */
/*   Updated: 2022/11/18 07:28:26 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	can_move(int y, int x, t_map *map)
{
	char	c;

	c = map->map_grid[y][x];
	if (c == '0' || (c > 5 + 48 && c < 10 + 48))
		return (1);
	if (c == 'D')
		if (map->door_map[y][x].open == 1)
			return (1);
	return (0);
}

static void	move_horizontal(int keycode, t_game *game)
{
	if (keycode == KEY_W)
	{
		if (can_move((int)game->player.pos.y, (int)(game->player.pos.x
				+ game->player.dir.x * PLAYER_MOVE_SPEED * 1.1), game->map))
			game->player.pos.x += game->player.dir.x * PLAYER_MOVE_SPEED;
		if (can_move((int)(game->player.pos.y + game->player.dir.y
				* PLAYER_MOVE_SPEED), (int)(game->player.pos.x), game->map))
			game->player.pos.y += game->player.dir.y * PLAYER_MOVE_SPEED;
	}
	if (keycode == KEY_S)
	{
		if (can_move((int)game->player.pos.y, (int)(game->player.pos.x
				- game->player.dir.x * PLAYER_MOVE_SPEED * 1.1), game->map))
			game->player.pos.x -= game->player.dir.x * PLAYER_MOVE_SPEED;
		if (can_move((int)(game->player.pos.y - game->player.dir.y
				* PLAYER_MOVE_SPEED), (int)(game->player.pos.x), game->map))
			game->player.pos.y -= game->player.dir.y * PLAYER_MOVE_SPEED;
	}
}

static void	move_vertical(int keycode, t_game *game)
{
	double	move_dir_x;
	double	move_dir_y;
	double	rotate_speed;

	if (keycode == KEY_D)
		rotate_speed = 1.5708;
	else
		rotate_speed = -1.5708;
	move_dir_x = game->player.dir.x * cos(rotate_speed)
		- game->player.dir.y * sin(rotate_speed);
	move_dir_y = game->player.dir.x * sin(rotate_speed)
		+ game->player.dir.y * cos(rotate_speed);
	if (can_move((int)game->player.pos.y, (int)(game->player.pos.x
			+ move_dir_x * PLAYER_MOVE_SPEED * 1.1), game->map))
		game->player.pos.x += move_dir_x * PLAYER_MOVE_SPEED;
	if (can_move((int)(game->player.pos.y + move_dir_y
			* PLAYER_MOVE_SPEED * 1.1), (int)game->player.pos.x, game->map))
		game->player.pos.y += move_dir_y * PLAYER_MOVE_SPEED;
}

void	player_move(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == KEY_S)
		move_horizontal(keycode, game);
	if (keycode == KEY_D || keycode == KEY_A)
		move_vertical(keycode, game);
}
