#include <cub3d.h>

static int init_sprites(t_game *game)
{
	int i;

	game->sprite = malloc(sizeof(t_sprite *));
	if (!game->sprite)
		return (1);
	i = -1;
	while (++i < game->map->sprite_count)
	{
		game->sprite[i] = malloc(sizeof(t_sprite));
		if (!game->sprite[i])
			return (1);
	}
	if (!game->sprite)
		return (1);
	game->sprite[game->map->sprite_count] = NULL;
	game->zBuffer = malloc(sizeof(double) * WIDTH);
	if (!game->zBuffer)
		return (1);
	return (0);
}

int scan_grid(t_map *map)
{
	int x;
	int y;
	size_t len_line;
	int sprite_index;

	y = -1;
	sprite_index = -1;
	if (init_sprites(map->game) == 1)
		return (1);
	while (++y < map->height)
	{
		len_line = ft_strlen(map->map_grid[y]);
		if (len_line > map->width)
			map->width = len_line;
		x = -1;
		while (map->map_grid[y][++x])
		{
			if (parse_tile(x, y, map, &sprite_index) == 1)
				return (1);
		}
	}
	if (map->player_orientation == '\0')
		return (parse_error_message("No player\n", -1));
	return (0);
}

static int get_sprite_count(char *s, t_map *map)
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

	map->height = ft_lstsize(map->grid_ptr);
	map->map_grid = malloc(sizeof(char *) * (map->height + 1));
	if (!map->map_grid)
		return (1);
	line_ptr = map->grid_ptr;
	if (!map->map_grid)
		return (1);
	y = -1;
	while (++y < map->height)
	{
		map->map_grid[y] = ft_strdup(line_ptr->content);
		if (!map->map_grid[y])
			return (1);
		map->sprite_count += get_sprite_count(map->map_grid[y], map);
		line_ptr = line_ptr->next;
	}
	map->map_grid[y] = NULL;
	return (0);
}

int parse_grid(t_map *map)
{
	if (copy_grid(map) == 1)
		return (1);
	if (scan_grid(map) == 1)
		return (1);
}
