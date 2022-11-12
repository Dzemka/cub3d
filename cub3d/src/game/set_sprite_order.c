#include <cub3d.h>

void get_distance(t_game *game)
{
	int i;
	t_coord *coord;

	i = -1;
	while (++i < game->map->sprite_count)
	{
		coord = game->sprite[i]->coord;
		game->sprite[i]->distance = (game->player.pos.x - coord->x) * (game->player.pos.x - coord->x) + (game->player.pos.y - coord->y) * (game->player.pos.y - coord->y);
		game->sprite[i]->order = 0;

	}
}

void compare_distance(t_sprite **sprite, int pos, t_game *game)
{
	int i;
	int order;
	t_sprite *temp;

	i = -1;
	order = 0;
	while (++i < game->map->sprite_count)
	{
		if (i != pos)
		{
			if (sprite[pos]->distance < sprite[i]->distance)
				order++;
			if (sprite[pos]->distance == sprite[i]->distance && sprite[i]->order != 0)
				order++;
		}
	}
	sprite[pos]->order = order;
}

void sort_sprites(t_game *game)
{
	int i;
	int order;
	t_sprite *temp;

	i = -1;
	while (++i < game->map->sprite_count)
		compare_distance(game->sprite, i, game);
	i = -1;
	while (++i < game->map->sprite_count)
	{
		order = game->sprite[i]->order;
		if (order != i)
		{
			temp = game->sprite[order];
			game->sprite[order] = game->sprite[i];
			game->sprite[i] = temp;
		}
	}
}

void set_sprite_order(t_game *game)
{
	get_distance(game);
	sort_sprites(game);
}
