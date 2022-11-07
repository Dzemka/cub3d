#include <cub3d.h>

void draw_basic(t_game *game)
{
	int	y;
	int	x;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			if (y < HEIGHT / 2 + game->pitch)
				game->buffer[y][x] = game->map->ceiling_color;
			else
				game->buffer[y][x] = game->map->floor_color;
		}
	}
}
