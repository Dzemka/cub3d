#include <cub3d.h>

int parse_exit(char *message, int id)
{
	char	c;

	if (id == NO_TEXTURE)
		write(1, "Texture with id \"NO\" error: ", 28);
	else if (id == SO_TEXTURE)
		write(1, "Texture with id \"SO\" error: ", 28);
	else if (id == EA_TEXTURE)
		write(1, "Texture with id \"EA\" error: ", 28);
	else if (id == WE_TEXTURE)
		write(1, "Texture with id \"WE\" error: ", 28);
	else if (id == FLOOR_COLOR)
		write(1, "Ambient with id \"F\" error: ", 27);
	else if (id == CEILLING_COLOR)
		write(1, "Ambient with id \"C\" error: ", 27);
	else if (id > 3 && id <= TEX_COUNT)
	{
		c = id + 48 - 4;
		write(1, "Sprite texture with id \"S", 26);
		write(1, &c, 1);
		write(1, "\" error: ", 10);
	}
	write(1, message, ft_strlen(message));
	exit(1);
}

void fill_coord(double y, double x, t_coord *pos)
{
	pos->x = x;
	pos->y = y;
}

void	rgb_to_num(char **rgb, int *set_color)
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
