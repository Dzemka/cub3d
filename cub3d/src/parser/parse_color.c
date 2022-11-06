#include <cub3d.h>

static void check_correct(char **rgb, int id)
{
	int i;
	int j;

	if (!rgb)
		game_exit("Get color error");
	i = -1;
	while (rgb[++i])
	{
		if (i >= 3)
			parse_exit("The RGB format consists of 3 numbers", id);
		j = -1;
		while (rgb[i][++j])
		{
			if (!ft_isdigit(rgb[i][j]))
				parse_exit("RGB consists only of numbers", id);
		}
		if (j > 3)
			parse_exit("Max RGB code is 255", id);
	}
}

static void	rgb_to_num(char **rgb, int *set_color)
{
	int	i;
	int	color;

	color = 0;
	i = -1;
	while (++i < 3)
	{
		color = ft_atoi(rgb[i]);
		if (color > 255)
			game_exit("Max RGB code is 255");
		*set_color += color * pow(256, 2 - i);
	}
}

static void	get_rgb(char *s, int pos, int id, int *color)
{
	char **rgb;
	int	i;

	rgb = ft_split(&s[pos], ',');
	check_correct(rgb, id);
	rgb_to_num(rgb, color);
	i = -1;
	while (rgb[++i])
		free(rgb[i]);
	free(rgb);
}

static void set_color(char *s, int i, int *color, int ambient_id)
{
	if (*color != -1)
		parse_exit("ambient color declared more than once\n", ambient_id);
	else
		(*color)++;
	if (s[i] == '\0')
		parse_exit("color not found\n", ambient_id);
	if (s[i] != ' ' && s[i] != '\t')
		parse_exit("no separator\n", ambient_id);
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	if (s[i - 1] == '\0')
		parse_exit("color not found\n", ambient_id);
	get_rgb(s, i, ambient_id, color);
}

int parse_color(char *s, int i, t_map *map)
{
	int	id;


	if (s[i] == 'F')
		set_color(s, i + 1, &map->floor_color, FLOOR_COLOR);
	else if (s[i] == 'C')
		set_color(s, i + 1, &map->ceiling_color, CEILLING_COLOR);
	else
		return (0);
	return (1);
}
