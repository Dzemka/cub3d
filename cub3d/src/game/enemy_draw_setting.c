#include <cub3d.h>

static void move(t_game *game, int id, int i)
{
	int j;
	double move_x;
	double move_y;

	if (game->player.pos.x < game->sprite[i]->coord->x)
		move_x = -0.3;
	else
		move_x = 0.3;
	if (game->player.pos.y < game->sprite[i]->coord->y)
		move_y = -0.3;
	else
		move_y = 0.3;
	j = -1;
	while (game->sprite[++j])
	{
			if (game->sprite[j]->coord->x == game->sprite[i]->coord->x + move_x * 20)
				move_x = 0;
			if (game->sprite[j]->coord->y == game->sprite[i]->coord->y + move_y * 20)
				move_y = 0;
	}
	move_x += game->sprite[i]->coord->x;
	move_y += game->sprite[i]->coord->y;
	fill_coord(move_y, move_x, game->sprite[i]->coord);
}

static void move_action(t_game *game, int id, int i)
{

	game->enemy[id]->frame++;
	if (game->enemy[id]->frame > 10)
	{
		move(game, id, i);
		game->enemy[id]->frame = 0;
		game->enemy[id]->action++;
	}
	if (game->enemy[id]->action > game->enemy[id]->count_spawn + game->enemy[id]->count_walk)
		game->enemy[id]->action = game->enemy[id]->count_spawn + 1;
}

void	attack_action(t_game *game, int id, int i)
{
	int	attack_index;

	attack_index = game->enemy[id]->count_spawn + game->enemy[id]->count_walk;
	if (game->enemy[id]->action < attack_index)
		game->enemy[id]->action = attack_index;
	game->enemy[id]->frame++;
	if (game->enemy[id]->frame > 20)
	{
		game->enemy[id]->action++;
		game->enemy[id]->frame = 0;
	}
	if (game->enemy[id]->action > attack_index + game->enemy[id]->count_attack)
	{
		game->enemy[id]->action = 0;
		game->enemy[id]->frame = 0;
	}
}

void select_action(t_game *game, int id, t_sprite_draw *draw_data, int i)
{
	int sprite_index;

	if (game->sprite[i]->distance < 1)
		attack_action(game, id, i);
	else if (game->enemy[id]->action > game->enemy[id]->count_spawn)
		move_action(game, id, i);
	else if (game->sprite[i]->distance < 100.0)
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
	draw_data->start_tex_x = floor((double)game->tex_img[draw_data->tex_id]->width / (double)game->enemy[id]->count_actions * game->enemy[id]->action);
}

void enemy_draw_setting(int i, t_sprite_draw *draw_data, t_game *game)
{
	int j;
	int id;

	j = -1;
	id = game->sprite[i]->id - 8;
	if (id >= 0 && id <= 3)
	{
		draw_data->step_x /= game->enemy[id]->count_actions;
		select_action(game, id, draw_data, i);
	}
}
