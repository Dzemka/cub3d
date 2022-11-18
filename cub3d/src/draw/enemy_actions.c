/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <olugash@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 06:46:42 by olugash           #+#    #+#             */
/*   Updated: 2022/11/18 06:58:53 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	death_action(t_game *game, int id)
{
	if (game->enemy[id]->action
		== game->enemy[id]->count_actions - 1)
		game->enemy[id]->action
			= game->enemy[id]->count_actions - 1;
	else if (game->enemy[id]->action
		< game->enemy[id]->count_actions - game->enemy[id]->count_dead - 1)
		game->enemy[id]->action
			= game->enemy[id]->count_actions - game->enemy[id]->count_dead;
	else if (game->enemy[id]->frame % (int)(ENEMY_DEATH_SPEED
		/ (game->enemy[id]->count_dead + 1) + 1) == 0)
		game->enemy[id]->action++;
}

void	spawn_action(int id, t_game *game)
{
	game->enemy[id]->frame++;
	if (game->enemy[id]->action >= game->enemy[id]->count_actions)
	{
		game->enemy[id]->action = 0;
		game->enemy[id]->frame = 0;
	}
	if (game->enemy[id]->frame % (int)(ENEMY_SPAWN_SPEED
		/ (game->enemy[id]->count_spawn + 1) + 1) == 0)
	{
		game->enemy[id]->action++;
		game->enemy[id]->frame = 0;
	}
}

static void	move(t_game *game, int i, double move_x, double move_y)
{
	double	y;
	double	x;
	char	c;

	x = game->sprite[i]->coord.x;
	y = game->sprite[i]->coord.y;
	if (game->player.pos.x < x)
		move_x *= -1;
	if (game->player.pos.y < y)
		move_y *= -1;
	c = game->map->map_grid[(int)(y + move_y)][(int)(x)];
	if ((c != '0' && c != game->sprite[i]->id + 48 - 2)
		|| ((int)(y) == (int)(game->player.pos.y)))
		move_y = 0;
	c = game->map->map_grid[(int)(y)][(int)(x + move_x)];
	if ((c != '0' && c != game->sprite[i]->id + 48 - 2)
		|| ((int)(x) == (int)(game->player.pos.x)))
		move_x = 0;
	move_x += x;
	move_y += y;
	game->map->map_grid[(int)y][(int)x] = '0';
	game->map->map_grid[(int)move_y][(int)move_x]
		= game->sprite[i]->id + 48 - 2;
	fill_coord(move_y, move_x, &game->sprite[i]->coord);
}

void	move_action(t_game *game, int id, int i)
{
	double	move_x;
	double	move_y;

	move_x = 0.05;
	move_y = 0.05;
	if (game->enemy[id]->frame % (100 / ENEMY_MOVE_SPEED) == 0)
		move(game, i, move_x, move_y);
	if (game->enemy[id]->frame % (ENEMY_WALK_SPEED
			/ (game->enemy[id]->count_walk + 1) + 1) == 0)
		game->enemy[id]->action++;
	if (game->enemy[id]->frame > 100)
		game->enemy[id]->frame = 0;
	if (game->enemy[id]->action > game->enemy[id]->count_spawn
		+ game->enemy[id]->count_walk)
		game->enemy[id]->action = game->enemy[id]->count_spawn + 1;
}

void	attack_action(t_game *game, int id)
{
	int	attack_index;

	attack_index = game->enemy[id]->count_spawn + game->enemy[id]->count_walk;
	if (game->enemy[id]->action < attack_index)
		game->enemy[id]->action = attack_index;
	if (game->enemy[id]->frame % (int)(ENEMY_ATTACK_SPEED
		/ (game->enemy[id]->count_attack + 1) + 1) == 0)
		game->enemy[id]->action++;
	if (game->enemy[id]->action > attack_index + game->enemy[id]->count_attack)
	{
		game->enemy[id]->action = attack_index;
		game->player.health -= ENEMY_DAMAGE;
		if (game->player.health <= 0)
			game->funct = &draw_dead_screen;
	}
}
