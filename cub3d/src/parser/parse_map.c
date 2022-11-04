#include <cub3d.h>

static int parse_id(char *s, int i, t_map *map)
{
	int status;

	status = -1;

	status = parse_textures(s, i, map);
	if (status == 1 || status == 0)
		return (status);
	status = parse_color(s, i, map);
	if (status == 1 || status == 0)
		return (status);
	if (status == -1)
	{
		if (!ft_strchr("0123456789", s[i]))
		{
			printf("%s : Undefined id\n", s);
			return (1);
		}
	}
	return (0);
}

static int parse_line(char *s, t_map *map, t_list *tmp)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(s);
	if (s[len - 1] == '\n')
		s[len - 1] = '\0';
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	if (map->grid_ptr)
		return (0);
	if (s[i] == '\0')
		return (0);
	if (parse_id(s, i, map))
		return (1);
	if (ft_strchr("0123456789", s[i]))
		map->grid_ptr = tmp;
	return (0);
}

static int read_line(t_map *map, int fd)
{
	t_list *ptr;
	char *line;

	line = get_next_line(fd);
	if (!line)
		return (-1);
	ptr = ft_lstnew(line);
	if (!ptr)
		return (parse_error_message("Malloc error\n", -1));
	ft_lstadd_back(&map->map_base, ptr);
	return (parse_line(line, map, ptr));
}

int parse_map(t_map *map, int fd)
{
	int status;

	map->grid_ptr = NULL;
	while (status != -1)
	{
		status = read_line(map, fd);
		if (status == 1)
			return (1);
	}
	if (copy_grid(map))
		return (1);
	if (map->player_orientation == '\0')
		return (parse_error_message("No player\n", -1));
	return (0);
}
