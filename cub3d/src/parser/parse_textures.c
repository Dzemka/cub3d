#include <cub3d.h>

static int parse_path(char *line, int pos, char **texture_ptr, int texture_id)
{
	if (*texture_ptr)
		return (parse_error_message("texture declared more than once\n",
									texture_id));
	if (line[pos] == '\0')
		return (parse_error_message("path not found\n", texture_id));
	if (line[pos] != ' ' && line[pos] != '\t')
		return (parse_error_message("no separator\n", texture_id));
	while (line[pos] == ' ' || line[pos] == '\t')
		pos++;
	if (line[pos] == '\0')
		return (parse_error_message("path not found\n", texture_id));
	*texture_ptr = ft_strdup(&line[pos]);
	if (!*texture_ptr)
		return (parse_error_message("malloc error\n", texture_id));
	return (0);
}

int parse_textures(char *s, int i, t_map *map)
{
	char c1;
	char c2;

	if (ft_strlen(&s[i]) < 2)
		return (-1);
	c1 = s[i];
	c2 = s[i + 1];
	if (c1 == 'N' && c2 == 'O')
		return (parse_path(s, i + 2, &map->path_textures[NO_TEXTURE], NO_TEXTURE));
	else if (c1 == 'S' && c2 == 'O')
		return (parse_path(s, i + 2, &map->path_textures[SO_TEXTURE], SO_TEXTURE));
	else if (c1 == 'W' && c2 == 'E')
		return (parse_path(s, i + 2, &map->path_textures[WE_TEXTURE], WE_TEXTURE));
	else if (c1 == 'E' && c2 == 'A')
		return (parse_path(s, i + 2, &map->path_textures[EA_TEXTURE], EA_TEXTURE));
	else if (c1 == 'S' && ft_strchr("0123456789", c2))
		return (parse_path(s, i + 2, &map->path_textures[c2 - 44], c2 - 44));
	else
		return (-1);
	return (0);
}
