#include <cub3d.h>

static void scan_grid(t_map *map)
{
	int		x;
	int		y;
	size_t	len_line;
	int		sprite_index;

	y = -1;
	sprite_index = -1;
	while (++y < map->height)
	{
		x = -1;
		while (map->map_grid[y][++x])
			parse_tile(x, y, map, &sprite_index);
		x--;
		while (++x < map->width)
			map->map_grid[y][x] = '-';
	}
}

static void init_sprites(t_game *game)
{
	int i;

	game->map->sprite_base = malloc(sizeof(t_sprite *) * (game->map->sprite_count + 1));
	if (!game->map->sprite_base)
		game_exit("Malloc error\n");
	i = -1;
	while (++i < game->map->sprite_count)
	{
		game->map->sprite_base[i] = malloc(sizeof(t_sprite));
		if (!game->map->sprite_base[i])
			game_exit("Malloc error\n");
		game->map->sprite_base[i]->id = -1;
	}
	game->map->sprite_base[game->map->sprite_count] = NULL;
}

static void get_sprite_count(char *s, t_map *map)
{
	int x;

	x = -1;
	while (s[++x])
	{
		if (ft_strchr("23456789", s[x]))
			map->sprite_count++;
	}
}

static int copy_grid(t_map *map)
{
	t_list *line_ptr;
	int y;
	int	i;

	map->height = ft_lstsize(map->grid_ptr);
	map->map_grid = malloc(sizeof(char *) * (map->height + 1));
	if (!map->map_grid)
		game_exit("Malloc error\n");
	line_ptr = map->grid_ptr;
	y = -1;
	while (++y < map->height)
	{
		map->map_grid[y] = malloc(sizeof(char) * map->width);
		if (!map->map_grid[y])
			game_exit("Malloc error");
		ft_strlcpy(map->map_grid[y], line_ptr->content, map->width);
		if (ft_strchr(map->map_grid[y], '\t'))
			game_exit("Map grid can not contain a tab");
		get_sprite_count(map->map_grid[y], map);
		line_ptr = line_ptr->next;
	}
	map->map_grid[y] = NULL;
}

void parse_grid(t_game *game)
{
	copy_grid(game->map);
	init_sprites(game);
	scan_grid(game->map);
}
