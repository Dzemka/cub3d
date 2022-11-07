#include <cub3d.h>

void draw_walls(t_game *game)
{
	int x;
	int drawStart;
	int drawEnd;

	x = -1;

	while (++x < WIDTH)
		get_verline(x, game, &drawStart, &drawEnd);
}
