#include <cub3d.h>

#include <pthread.h>

void *draw(void *arg)
{
	t_game *game;
	t_tid *tid;
	int y_end;
	int y;
	int x;

	tid = (t_tid *)arg;
	game = tid->game;
	y_end = tid->y + HEIGHT / 16;
	y = tid->y;
	y--;

	while (++y < y_end)
	{
		x = -1;
		while (++x < WIDTH)
		{
			ft_pixel_put(&game->img, x, y, game->buffer[y][x]);
		}
	}
}

void draw_walls(t_game *game)
{
	int x;
	int drawStart;
	int drawEnd;

	x = -1;
	while (++x < WIDTH)
		get_verline(x, game, &drawStart, &drawEnd);
	int tx;
	int ty;
	ty = -1;
	// while (++ty < HEIGHT)
	// {
	// 	tx = -1;
	// 	while (++tx < WIDTH)
	// 	{
	// 		if (game->buffer[ty][tx] != 0xFF000000)
	// 			ft_pixel_put(&game->img, tx, ty, game->buffer[ty][tx]);
	// 	}
	// }
	ty = -1;
	// while (++ty < HEIGHT)
	// {
	// 	x = -1;
	// 	while (++tx < WIDTH)
	// 	{
	// 		game->buffer[ty][x] = 0x0;
	// 	}
	// }
	game->wall_color = 0x0;
}
