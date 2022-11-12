#include <cub3d.h>

void check_correct(char *line, int *pos, t_map *map, int texture_id)
{
	if (map->path_textures[texture_id])
		parse_exit("texture declared more than once\n", texture_id);
	if (line[*pos] == '\0')
		parse_exit("path not found\n", texture_id);
	if (line[*pos] != ' ' && line[*pos] != '\t')
		parse_exit("no separator\n", texture_id);
	while (line[*pos] == ' ' || line[*pos] == '\t')
		(*pos)++;
	if (line[*pos] == '\0')
		parse_exit("path not found\n", texture_id);
}

static void parse_path(char *line, int pos, t_map *map, int texture_id)
{
	check_correct(line, &pos, map, texture_id);
	map->path_textures[texture_id] = ft_strdup(&line[pos]);
	if (!map->path_textures[texture_id])
		game_exit("Malloc error\n");
}

int parse_textures(char *s, int pos, t_map *map)
{
	char c1;
	char c2;
	int id;

	if (ft_strlen(&s[pos]) < 2)
		return (0);
	c1 = s[pos];
	c2 = s[pos + 1];
	if (c1 == 'N' && c2 == 'O')
		id = NO_TEXTURE;
	else if (c1 == 'S' && c2 == 'O')
		id = SO_TEXTURE;
	else if (c1 == 'W' && c2 == 'E')
		id = WE_TEXTURE;
	else if (c1 == 'E' && c2 == 'A')
		id = EA_TEXTURE;
	else if (c1 == 'S')
	{
		if (!ft_strchr("01234567", c2))
			game_exit("The range of sprite id is 0-7");
		id = c2 - 48 + 4;
	}
	else
		return (0);
	parse_path(s, pos + 2, map, id);
	return (1);
}
