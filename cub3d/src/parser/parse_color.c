#include <cub3d.h>

static int is_correct_rgb(char *s, int i, int *count_numbers, int ambient_id)
{
	int start;

	start = i;
	while (s[i])
	{
		if (!ft_isdigit(s[i]) && s[i] != '\0' && s[i] != ',')
			return (parse_error_message("color setting error\n", ambient_id));
		if (s[i] == ',')
		{
			if (i - start > 3)
				return (parse_error_message("Max RGB code is 255\n",
											ambient_id));
			if (i - start == 3 && s[start] >= '2' && s[start + 1] >= '5' &&
				s[start + 2] > '5')
				return (parse_error_message("Max RGB code is 255\n",
											ambient_id));
			start = i + 1;
			(*count_numbers)++;
		}
		i++;
	}
	return (0);
}

static int check_rgb(char *s, int i, int ambient_id)
{
	int count_numbers;

	count_numbers = 1;
	if (is_correct_rgb(s, i, &count_numbers, ambient_id) == 1)
		return (1);
	if (count_numbers != 3)
		return (parse_error_message("The RGB format consists of 3 numbers "
									"written separated by commas\n",
									ambient_id));
	return (0);
}

static int fill_rgb(char ***rgb_str, int *color)
{
	int i;
	int num;

	i = -1;
	while (++i < 3)
		*color = ft_atoi((*rgb_str)[i]) * pow(256, 3 - i - 1) + *color;
	i = -1;
	while (++i < 3)
		free((*rgb_str)[i]);
	free(*rgb_str);
	return (0);
}

static int set_color(char *s, int i, int *color, int ambient_id)
{
	int temp_pos;
	char **rgb_str;

	if (*color != -1)
		return (parse_error_message("ambient color declared more than once\n",
									ambient_id));
	else
		(*color)++;
	if (s[i] == '\0')
		return (parse_error_message("color not found\n", ambient_id));
	if (s[i] != ' ' && s[i] != '\t')
		return (parse_error_message("no separator\n", ambient_id));
	while (s[i] == ' ' || s[i] == '\0')
		i++;
	if (s[i - 1] == '\0')
		return (parse_error_message("color not found\n", ambient_id));
	if (check_rgb(s, i, ambient_id) == 1)
		return (1);
	rgb_str = ft_split(&s[i], ',');
	if (!rgb_str)
		return (parse_error_message("malloc error\n", ambient_id));
	return (fill_rgb(&rgb_str, color));
}

int parse_color(char *s, int i, t_map *map)
{
	if (s[i] == 'F')
		return (set_color(s, i + 1, &map->floor_color, FLOOR_COLOR));
	if (s[i] == 'C')
		return (set_color(s, i + 1, &map->ceiling_color, CEILLING_COLOR));
	else
		return (-1);
	return (0);
}
