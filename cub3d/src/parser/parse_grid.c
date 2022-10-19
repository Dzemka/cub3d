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

static int check_walls(t_map *map)
{
	int x;
	int y;
	int len_str;

	y = -1;
	while (++y < map->height)
	{
		x = -1;
		len_str = ft_strlen(map->map_grid[y]);
		if (len_str > map->width)
			map->width = len_str;
		while (++x < len_str)
		{
			if (map->map_grid[y][x] == '0' || map->map_grid[y][x] == map->player_orientation)
			{
				if (check_around(map, y, x, len_str))
					return (parse_error_message("The walls are not closed\n", -1));
			}
		}
	}
	return (0);
}

int copy_grid(t_list *ptr, t_map *map)
{
	int i;

	i = 0;
	map->height = ft_lstsize(ptr);
	map->map_grid = malloc(sizeof(char *) * (map->height + 1));
	while (ptr)
	{
		map->map_grid[i] = ft_strdup(ptr->content);
		if (!map->map_grid[i])
			return (parse_error_message("Malloc error\n", -1));
		if (ft_strchr(map->map_grid[i], map->player_orientation))
			map->player_p.y = i;
		i++;
		ptr = ptr->next;
	}
	map->map_grid[i] = NULL;
	return (check_walls(map));
}

int parse_grid(char *s, int i, t_map *map)
{
	while (s[i] != '\0')
	{
		if (!ft_strchr("0123456789NSEW ", s[i]))
		{
			printf("Line %d, Column %d : \"%c\" - undefined symbol\n",
				   ft_lstsize(map->map_base), i + 1, s[i]);
			return (1);
		}
		if (ft_strchr("NSWE", s[i]))
		{
			if (map->player_orientation != '\0')
				return (parse_error_message("Player declared more than once\n", -1));
			map->player_orientation = s[i];
			map->player_p.x = i;
		}
		i++;
	}
	return (0);
}
