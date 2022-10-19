#include <cub3d.h>

void ft_pixel_put(t_data_img *data, int x, int y, int color)
{
	*(int *)(data->addr + (y * data->line_length + x * (data->bpp / 8))) = color;
}

void draw_basic(t_game *game)
{
	int x;
	int y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			if (y < HEIGHT / 2)
				game->buffer[y][x] = game->map->ceiling_color;
			else
				game->buffer[y][x] = game->map->floor_color;
		}
	}
}

void game_start(t_game *game)
{
	draw_basic(game);
	draw_floor(game);
	draw_walls(game);
	draw_sprites(game);
	mlx_put_image_to_window(game->mlx, game->window, game->img.img, 0, 0);

}
