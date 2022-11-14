#include <cub3d.h>

static void get_enemy(t_game *game)
{
	int i;

	i = -1;
	while (++i < ENEMY_COUNT)
		*game->enemy[i] = *game->map->enemy_base[i];
}

static void get_player_orientation(t_game *game)
{
	if (game->map->player_orientation == 'N')
	{
		fill_coord(-1, 0, &game->player.dir);
		fill_coord(0, FOV, &game->player.plane);
	}
	else if (game->map->player_orientation == 'W')
	{
		fill_coord(0, -1, &game->player.dir);
		fill_coord(-FOV, 0, &game->player.plane);
	}
	else if (game->map->player_orientation == 'S')
	{
		fill_coord(1, 0, &game->player.dir);
		fill_coord(0, -FOV, &game->player.plane);
	}
	else if (game->map->player_orientation == 'E')
	{
		fill_coord(0, 1, &game->player.dir);
		fill_coord(FOV, 0, &game->player.plane);
	}
	fill_coord(game->map->player_p.y + 0.5, game->map->player_p.x + 0.5, &game->player.pos);
	game->map->map_grid[(int)game->map->player_p.y][(int)game->map->player_p.x] = '0';
	game->player.health = 100;
	game->pitch = 0;
}

static void get_sprites(t_game *game)
{
	int i;
	int x;
	int y;
	int sprite_index;

	y = -1;
	while (++y < game->map->height)
	{
		x = -1;
		while (game->map->map_grid[y][++x])
		{
			if (ft_strchr("6789", game->map->map_grid[y][x]))
				game->map->map_grid[y][x] = '0';
		}
	}
	i = -1;
	while (++i < game->map->sprite_count)
		*game->sprite[i] = *game->map->sprite_base[i];
}

void get_start(t_game *game)
{
	get_sprites(game);
	get_enemy(game);
	get_player_orientation(game);
	game->funct = &draw_game;
}
