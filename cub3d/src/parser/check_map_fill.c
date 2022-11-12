#include <cub3d.h>

static void check_setting(t_game *game)
{
	int i;

	i = -1;
	while (game->map->enemy_base[++i])
		if (game->map->enemy_base[i]->sprite_index == -1)
			game_exit("Enemy setting not declared");
}

static void check_on_map(t_game *game)
{
	int i;
	int j;
	int enemy_count;
	int id;

	i = -1;
	enemy_count = 0;
	while (++i < game->map->sprite_count)
	{
		id = game->map->sprite_base[i]->id;
		if (id >= 8 && id <= 11)
		{
			enemy_count++;

			j = -1;
			while (++j < game->map->sprite_count)
				if (j != i && game->map->sprite_base[i]->id == game->map->sprite_base[j]->id)
					game_exit("There should only be one type of enemy on the map");
		}
	}
	if (enemy_count != 4)
		game_exit("Must be 4 enemies on map");
}

static void check_enemy(t_game *game)
{
	check_setting(game);
	check_on_map(game);
}

static void check_textures(t_game *game)
{
	int i;

	i = -1;
	while (game->map->path_textures[++i] != NULL);
	if (i < 12)
		game_exit("Not enought texture path");
}

void check_map_fill(t_game *game)
{
	if (!game->map->grid_ptr)
		game_exit("No map");
	if (game->map->player_orientation == '\0')
		game_exit("No player");
	if (game->map->floor_color == -1)
		game_exit("Floor color not declared");
	if (game->map->ceiling_color == -1)
		game_exit("Ceilling color not declared");
	check_textures(game);
	check_enemy(game);
}
