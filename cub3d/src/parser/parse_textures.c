#include <cub3d.h>

static int parse_path(char *line, int pos, char **texture_ptr, int texture_id)
{
	// if (*texture_ptr)
	// 	return (parse_error_message("texture declared more than once\n",
	// 								texture_id));
	if (line[pos] == '0')
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
	if (s[i] == 'N' && s[i + 1] == 'O')
		return (parse_path(s, i + 2, &map->path_textures[NO_TEXTURE], NO_TEXTURE));
	else if (s[i] == 'S' && s[i + 1] == 'O')
		return (parse_path(s, i + 2, &map->path_textures[SO_TEXTURE], SO_TEXTURE));
	else if (s[i] == 'W' && s[i + 1] == 'E')
		return (parse_path(s, i + 2, &map->path_textures[WE_TEXTURE], WE_TEXTURE));
	else if (s[i] == 'E' && s[i + 1] == 'A')
		return (parse_path(s, i + 2, &map->path_textures[EA_TEXTURE], EA_TEXTURE));
	else
		return (-1);
	return (0);
}
