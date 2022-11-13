#include <cub3d.h>

void spawn_action(int id, t_game *game)
{
	game->enemy[id]->frame++;
	if (game->enemy[id]->action >= game->enemy[id]->count_actions)
	{
		game->enemy[id]->action = 0;
		game->enemy[id]->frame = 0;
	}
	if (game->enemy[id]->frame > 50)
	{
		game->enemy[id]->action++;
		game->enemy[id]->frame = 0;
	}
}

static void move(t_game *game, int id, int i)
{
	double move_x;
	double move_y;
	char	c;
	
	if (game->player.pos.x < game->sprite[i]->coord->x)
		move_x = -0.05;
	else
		move_x = 0.05;
	if (game->player.pos.y < game->sprite[i]->coord->y)
		move_y = -0.05;
	else
		move_y = 0.05;
	if (floor(game->sprite[i]->coord->x) == floor(game->player.pos.x))
		move_x = 0;
	if (floor(game->sprite[i]->coord->y) == floor(game->player.pos.y))
		move_y = 0;
	c = game->map->map_grid[(int)(game->sprite[i]->coord->y + move_y)][(int)(game->sprite[i]->coord->x)];
	if (c != '0' && c != game->sprite[i]->id + 48 + 2)
		move_y = 0;
	c = game->map->map_grid[(int)(game->sprite[i]->coord->y)][(int)(game->sprite[i]->coord->x + move_x)];
	if (c != '0' && c != game->sprite[i]->id + 48 + 2)
		move_x = 0;
	move_x += game->sprite[i]->coord->x;
	move_y += game->sprite[i]->coord->y;
	game->map->map_grid[(int)game->sprite[i]->coord->y][(int)game->sprite[i]->coord->x] = '0';
	game->map->map_grid[(int)move_y][(int)move_x] = game->sprite[i]->id + 48 + 2;
	fill_coord(move_y, move_x, game->sprite[i]->coord);
}

void move_action(t_game *game, int id, int i)
{
	if (game->enemy[id]->frame % (100 / ENEMY_MOVE_SPEED) == 0)
		move(game, id, i);
	if (game->enemy[id]->frame % (5 * game->enemy[id]->count_walk) == 0)
		game->enemy[id]->action++;
	if (game->enemy[id]->frame > 100)
		game->enemy[id]->frame = 0;
	if (game->enemy[id]->action > game->enemy[id]->count_spawn + game->enemy[id]->count_walk)
		game->enemy[id]->action = game->enemy[id]->count_spawn + 1;
}

void attack_action(t_game *game, int id, int i)
{
	int attack_index;

	attack_index = game->enemy[id]->count_spawn + game->enemy[id]->count_walk;
	if (game->enemy[id]->action < attack_index)
		game->enemy[id]->action = attack_index;
	if (game->enemy[id]->frame % (int)(ENEMY_ATTACK_SPEED / game->enemy[id]->count_attack) == 0)
		game->enemy[id]->action++;
	if (game->enemy[id]->action > attack_index + game->enemy[id]->count_attack)
		game->enemy[id]->action = attack_index;
}
