#include <cub3d.h>

static int get_sprite_coord(int x, int y, t_map *map, int *sprite_index)
{
	t_game *game;

	game = map->game;
	*sprite_index += 1;
	game->sprite[*sprite_index]->id = map->map_grid[y][x] - 48 + 2;
	fill_coord(y + 0.5, x + 0.5, &game->sprite[*sprite_index]->coord);
}

static	int init_tile(int x, int y, t_map *map, int *sprite_index)
{
	char c;

	c = map->map_grid[y][x];
	if (ft_strchr("NSWE", c))
	{
		if (map->player_orientation != '\0')
			return (parse_error_message("Player must be only one\n", -1));
		map->player_orientation = c;
		fill_coord(y, x, &map->player_p);
	}
	if (ft_strchr("23456789", c))
		get_sprite_coord(x, y, map, sprite_index);
}

static int check_around(t_map *map, int y, int x, int len_str)
{
	if (y == 0 || y == map->height - 1)
		return (1);
	if (x == 0 || x == len_str - 1)
		return (1);
	if (x >= ft_strlen(map->map_grid[y + 1]))
		return (1);
	if (x >= ft_strlen(map->map_grid[y - 1]))
		return (1);
	if (map->map_grid[y][x - 1] == ' ')
		return (1);
	if (map->map_grid[y][x + 1] == ' ')
		return (1);
	if (map->map_grid[y - 1][x] == ' ')
		return (1);
	if (map->map_grid[y + 1][x] == ' ')
		return (1);
	return (0);
}

static int	check_tile(int x, int y, t_map *map)
{
	char c;

	c = map->map_grid[y][x];
	if (!ft_strchr("0123456789NSEW ", c))
	{
		printf("Line %d, Column %d : \"%c\" - undefined symbol\n",
			   y, x + 1, c);
		return (1);
	}
	if (map->map_grid[y][x] != '1')
		if (check_around(map, y, x, ft_strlen(map->map_grid[y])))
			return (parse_error_message("The walls are not closed\n", -1));
}

int parse_tile(int x, int y, t_map *map, int *sprite_index)
{
	if (check_tile(x, y, map) == 1)
		return (1);
	if (init_tile(x, y, map, sprite_index) == 1)
		return (1);
}
