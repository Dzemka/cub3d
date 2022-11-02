#include <cub3d.h>

int check_around(t_map *map, int y, int x, int len_str)
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

int	get_sprite_coord(int x, int y, t_map *map)
{
	t_game	*game;
	t_coord *coord;
	t_list	*pos;
	char	tex_id;

	game = map->game;
	coord = malloc(sizeof(t_coord));
	if (!coord)
		return (1);
	coord->x = x + 0.5;
	coord->y = y + 0.5;
	pos = ft_lstnew(coord);
	tex_id = game->map->map_grid[y][x] - 48;
	ft_lstadd_back(&game->sprite[tex_id]->pos, pos);
}

int scan_x(int x, int y, t_map *map)
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
	if (ft_strchr("NSWE", c))
	{
		if (map->player_orientation != '\0')
			return (parse_error_message("Player must be only one\n", -1));
		map->player_orientation = c;
		fill_coord(y, x, &map->player_p);
	}
	if (ft_strchr("23456789", c))
		get_sprite_coord(x, y, map);
}

int scan_grid(t_map *map)
{
	int x;
	int y;
	size_t len_line;

	y = -1;
	while (++y < map->height)
	{
		len_line = ft_strlen(map->map_grid[y]);
		if (len_line > map->width)
			map->width = len_line;
		x = -1;
		while (map->map_grid[y][++x])
			if (scan_x(x, y, map) == 1)
				return (1);
	}
	return (0);
}

int copy_grid(t_map *map)
{
	t_list *line_ptr;
	int y;

	line_ptr = map->grid_ptr;
	map->height = ft_lstsize(map->grid_ptr);
	map->map_grid = malloc(sizeof(char *) * (map->height + 1));
	if (!map->map_grid)
		return (1);
	y = -1;

	while (++y < map->height)
	{
		map->map_grid[y] = ft_strdup(line_ptr->content);
		if (!map->map_grid[y])
			return (1);
		line_ptr = line_ptr->next;
	}

	map->map_grid[y] = NULL;

	if (scan_grid(map) == 1)
		return (1);

}
