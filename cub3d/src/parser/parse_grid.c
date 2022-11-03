#include <cub3d.h>

int scan_grid(t_map *map)
{
	int x;
	int y;
	size_t len_line;
	int sprite_index;

	y = -1;
	sprite_index = 0;
	while (++y < map->height)
	{
		len_line = ft_strlen(map->map_grid[y]);
		if (len_line > map->width)
			map->width = len_line;
		x = -1;
		while (map->map_grid[y][++x])
			if (scan_x(x, y, map, &sprite_index) == 1)
				return (1);
	}
	return (0);
}

static int fill_massive(t_map *map)
{
	t_list *line_ptr;
	int y;
	int x;
	int len;

	line_ptr = map->grid_ptr;
	if (!map->map_grid)
		return (1);
	y = -1;
	while (++y < map->height)
	{
		x = -1;
		len = ft_strlen(line_ptr->content);
		while (++x < len)
		{
			if (ft_strchr("23456789", ((char *)line_ptr->content)[x]))
				map->sprite_count++;
		}
		map->map_grid[y] = ft_strdup(line_ptr->content);
		if (!map->map_grid[y])
			return (1);
		line_ptr = line_ptr->next;
	}
	map->map_grid[y] = NULL;
	return (0);
}

int init_sprites(t_game *game)
{
	int	i;

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

int copy_grid(t_map *map)
{
	map->map_grid = malloc(sizeof(char *) * (map->height + 1));
	if (!map->map_grid)
		return (1);
	map->height = ft_lstsize(map->grid_ptr);
	if (fill_massive(map) == 1)
		return (1);
	if (init_sprites(map->game) == 1)
		return (1);
	if (scan_grid(map) == 1)
		return (1);
}
