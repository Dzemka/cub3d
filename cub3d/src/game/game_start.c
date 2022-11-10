#include <cub3d.h>

void ft_pixel_put(t_data_img *data, int x, int y, int color)
{
	*(int *)(data->addr + (y * data->line_length + x * (data->bpp / 8))) = color;
}

int game_start(t_game *game)
{
	int x;
	int y;

	draw_basic(game);
	draw_walls(game);
	draw_sprites(game);

	int i;

	i = -1;
	while (game->sprite[++i])
	{
		game->sprite[i]->frame++;
		if (game->sprite[i]->frame >= 10)
		{
			double new_x;
			double new_y;

			new_x = game->sprite[i]->coord->x;
			new_y = game->sprite[i]->coord->y;
			if (game->player->pos->x > game->sprite[i]->coord->x)
				new_x = 0.1 + game->sprite[i]->coord->x;
			else if (game->player->pos->x < game->sprite[i]->coord->x)
				new_x = -0.1 + game->sprite[i]->coord->x;
			if (game->player->pos->y > game->sprite[i]->coord->y)
				new_y = 0.1 + game->sprite[i]->coord->y;
			else if (game->player->pos->y < game->sprite[i]->coord->y)
				new_y = -0.1 + game->sprite[i]->coord->y;
			fill_coord(new_y, new_x, game->sprite[i]->coord);
			game->sprite[i]->frame = 0;
		}
	}
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			ft_pixel_put(&game->img, x, y, game->buffer[y][x]);
	}
	mlx_put_image_to_window(game->mlx, game->window, game->img.img, 0, 0);
}
