#include <cub3d.h>

static void check_rgb_format(char **rgb, int id)
{
	int i;
	int j;

	if (!rgb)
		game_exit("Get color error");
	i = -1;
	while (rgb[++i])
	{
		if (i >= 3)
			parse_exit("The RGB format consists of 3 numbers\n", id);
		j = -1;
		while (rgb[i][++j])
		{
			if (!ft_isdigit(rgb[i][j]))
				parse_exit("RGB consists only of numbers\n", id);
		}
		if (j > 3)
			parse_exit("Max RGB code is 255", id);
	}
	if (i != 3)
		parse_exit("The RGB format consists of 3 numbers\n", id);
}

static void get_rgb(char *s, int pos, int id, int *color)
{
	char **rgb;
	int i;

	rgb = ft_split(&s[pos], ',');
	check_rgb_format(rgb, id);
	rgb_to_num(rgb, color);
	i = -1;
	while (rgb[++i])
		free(rgb[i]);
	free(rgb);
}

static void check_data(char *s, int *pos, int *color, int ambient_id)
{
	if (*color != -1)
		parse_exit("ambient color declared more than once\n", ambient_id);
	else
		(*color)++;
	if (s[*pos] == '\0')
		parse_exit("color not found\n", ambient_id);
	if (s[*pos] != ' ' && s[*pos] != '\t')
		parse_exit("no separator\n", ambient_id);
	while (s[*pos] == ' ' || s[*pos] == '\t')
		(*pos)++;
	if (s[*pos] == '\0')
		parse_exit("color not found\n", ambient_id);
}

static void set_color(char *s, int pos, int *color, int ambient_id)
{
	check_data(s, &pos, color, ambient_id);
	get_rgb(s, pos, ambient_id, color);
}

// the function returns 1 if the string contains a color and 0 if it does not
int parse_color(char *s, int i, t_map *map)
{
	int id;

	if (s[i] == 'F')
		set_color(s, i + 1, &map->floor_color, FLOOR_COLOR);
	else if (s[i] == 'C')
		set_color(s, i + 1, &map->ceiling_color, CEILLING_COLOR);
	else
		return (0);
	return (1);
}
