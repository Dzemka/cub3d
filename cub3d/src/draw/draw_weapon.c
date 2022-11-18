/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_weapon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <olugash@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 06:33:33 by olugash           #+#    #+#             */
/*   Updated: 2022/11/18 06:46:38 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	do_damage(t_game *game)
{
	size_t	p_x;
	size_t	p_y;
	int		row;
	int		col;
	char	c;

	p_x = (int)(game->player.pos.x);
	p_y = (int)(game->player.pos.y);
	row = -3;
	while (++row <= 2)
	{
		col = -3;
		while (++col <= 2)
		{
			if (p_y + row > 0 && p_y < game->map->height && p_x + col > 0)
			{
				if (p_x + col < ft_strlen(game->map->map_grid[p_y + row]))
				{
					c = game->map->map_grid[p_y + row][p_x + col];
					if (ft_strchr("6789", c))
						game->enemy[c - 48 - 6]->health -= PLAYER_DAMAGE;
				}
			}
		}
	}
}

static void	attack_animation(t_game *game)
{
	game->player.frame++;
	if (game->player.weapon_action < 2)
		game->player.weapon_action = 3;
	if (game->player.frame % 5 == 0)
		game->player.weapon_action++;
	if (game->player.frame == 100)
		game->player.frame = 0;
	if (game->player.weapon_action == 11)
	{
		game->player.weapon_action = 0;
		game->player.attack = 0;
		do_damage(game);
	}
}

static void	standart_animation(t_game *game)
{
	game->player.frame++;
	if (game->player.frame % 8 == 0)
		game->player.weapon_action++;
	if (game->player.frame == 100)
		game->player.frame = 0;
	if (game->player.weapon_action == 3)
		game->player.weapon_action = 0;
}

static void	fill_buffer(double step_x, double step_y,
	double start_x, t_game *game)
{
	int		x;
	int		y;
	double	tex_x;
	double	tex_y;

	tex_y = 0;
	y = HEIGHT / 2;
	while (++y < HEIGHT)
	{
		x = -1;
		tex_x = start_x;
		while (++x < WIDTH)
		{
			if (game->texture[13][(int)tex_y][(int)tex_x] != 16777216)
				game->buffer[y][x] = game->texture[13][(int)tex_y][(int)tex_x];
			tex_x += step_x;
		}
		tex_y += step_y;
	}
}

void	draw_weapon(t_game *game)
{
	double	step_x;
	double	step_y;
	double	start_x;

	if (game->player.attack == 1)
		attack_animation(game);
	else
		standart_animation(game);
	step_x = (double)(game->tex_img[13]->width - 1) / WIDTH / 11;
	step_y = (double)(game->tex_img[13]->height - 1) / HEIGHT * 2;
	start_x = game->tex_img[13]->width / 11 * game->player.weapon_action;
	fill_buffer(step_x, step_y, start_x, game);
}
