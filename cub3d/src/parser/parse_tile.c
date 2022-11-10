#include <cub3d.h>

static void	get_sprite(int x, int y, t_map *map, int *sprite_index)
{
	t_game *game;

	game = map->game;
	*sprite_index += 1;
	game->sprite[*sprite_index]->id = map->map_grid[y][x] - 48 + 2;
	game->sprite[*sprite_index]->coord = malloc(sizeof(t_coord));
	fill_coord(y + 0.5, x + 0.5, game->sprite[*sprite_index]->coord);
	game->sprite[*sprite_index]->frame = 0;
}

static void	init_tile(int x, int y, t_map *map, int *sprite_index)
{
	char c;

	c = map->map_grid[y][x];
	if (ft_strchr("NSWE", c))
	{
		if (map->player_orientation != '\0')
			game_exit("Player must be only one");
		map->player_orientation = c;
		map->player_p = malloc(sizeof(t_coord));
		fill_coord(y, x, map->player_p);
	}
	if (ft_strchr("23456789", c))
		get_sprite(x, y, map, sprite_index);
}

static int check_around(t_map *map, int y, int x, int len_str)
{
	return (y == 0 ||
			y == map->height - 1 ||
			x == 0 ||
			x == len_str - 1 ||
			x >= ft_strlen(map->map_grid[y + 1]) ||
			x >= ft_strlen(map->map_grid[y - 1]) ||
			map->map_grid[y][x - 1] == ' ' ||
			map->map_grid[y][x + 1] == ' ' ||
			map->map_grid[y - 1][x] == ' ' ||
			map->map_grid[y + 1][x] == ' ');
}

static void	check_tile(int x, int y, t_map *map)
{
	char c;

	c = map->map_grid[y][x];
	if (!ft_strchr("0123456789NSEW ", c))
	{
		printf("Line %d, Column %d : \"%c\" - undefined symbol\n",
			   y, x + 1, c);
		exit(1);
	}
	if (ft_strchr("023456789", map->map_grid[y][x]))
	{
		if (check_around(map, y, x, ft_strlen(map->map_grid[y])))
			game_exit("The walls are not closed");
	}
}

int parse_tile(int x, int y, t_map *map, int *sprite_index)
{
	check_tile(x, y, map);
	init_tile(x, y, map, sprite_index);
}
