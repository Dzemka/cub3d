#include <cub3d.h>

static void parse_id(char *s, int i, t_map *map, t_list *tmp)
{
	if (parse_textures(s, i, map))
		return;
	if (parse_color(s, i, map))
		return;
	if (ft_strchr("0123456789", s[i]))
		map->grid_ptr = tmp;
	else
	{
		printf("%s", s);
		game_exit(": undefined id");
	}
}

static void parse_line(char *s, t_map *map, t_list *tmp)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(s);
	if (s[len - 1] == '\n')
		s[len - 1] = '\0';
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	if (s[i] == '\0')
		return;
	if (!map->grid_ptr)
		parse_id(s, i, map, tmp);
}

static void read_line(t_map *map, int fd, int *read_end)
{
	t_list *ptr;
	char *line;

	line = get_next_line(fd);
	if (!line)
	{
		*read_end = 1;
		return;
	}
	ptr = ft_lstnew(line);
	if (!ptr)
		game_exit("Malloc error\n");
	ft_lstadd_back(&map->lineList, ptr);
	parse_line(line, map, ptr);
}

int parse_map(t_game *game, int fd)
{
	int read_end;

	read_end = 0;
	while (!read_end)
		read_line(game->map, fd, &read_end);
	if (parse_grid(game->map))
		return (1);
	ft_lstclear(&game->map->lineList, free);
	return (0);
}
