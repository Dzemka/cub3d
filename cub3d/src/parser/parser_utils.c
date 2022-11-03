#include <cub3d.h>

int parse_error_message(char *message, int id)
{
	printf("%d\n", id);
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
	else if (id == 0)
		write(1, "Sprite texture with id \"S0\" error: ", 36);
	write(1, message, ft_strlen(message));
	return (1);
}

void	fill_coord(double y, double x, t_coord *pos)
{
	pos->x = x;
	pos->y = y;
}

void	init_map_values(t_map *map)
{
	map->floor_color = -1;
	map->ceiling_color = -1;
	map->map_grid = NULL;
	map->map_base = NULL;
	map->width = 0;
	map->player_orientation = '\0';
	map->sprite_count = 0;
}
