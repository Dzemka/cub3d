#include <cub3d.h>

void ft_pixel_put(t_data_img *data, int x, int y, int color)
{
	*(int *)(data->addr + (y * data->line_length + x * (data->bpp / 8))) = color;
}

void draw_hp(t_game *game)
{
	int x;
	int y;
	int start_x;
	int width_frame;
	int scale;

	width_frame = WIDTH / 5;
	scale = width_frame * game->player.health / 100;
	y = game->coord_start_hp.y - 1;
	start_x = -1;
	while (game->health_frame_buffer[++y])
	{
		x = game->coord_start_hp.x - 1;
		while (game->health_frame_buffer[y][++x])
		{
			game->buffer[y][x] = 0xFF0000;
			if (game->health_frame_buffer[y][x] != 16777216)
			{
				if (start_x == -1)
					start_x = x;
				game->buffer[y][x] = game->health_frame_buffer[y][x];
				if (game->health_frame_buffer[y][x] == 0x1)
				{
					if (x < game->coord_start_hp.x + scale)
						game->buffer[y][x] = 0xFF0000;
				}
			}
		}
	}
}

int draw_game(t_game *game)
{
	int x;
	int y;

	draw_basic(game);
	draw_walls(game);
	draw_sprites(game);
	draw_weapon(game);
	draw_minimap(game);
	draw_hp(game);
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			ft_pixel_put(&game->img, x, y, game->buffer[y][x]);
	}
	mlx_put_image_to_window(game->mlx, game->window, game->img.img, 0, 0);
	return (0);
}

int draw_dead_screen(t_game *game)
{
	int x;
	int y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			ft_pixel_put(&game->img, x, y, 0x0);
	}
	mlx_put_image_to_window(game->mlx, game->window, game->img.img, 0, 0);
	mlx_string_put(game->mlx, game->window, WIDTH / 2, HEIGHT / 2, 0xFF0000, "You are dead");
	mlx_string_put(game->mlx, game->window, WIDTH / 2 - 20, HEIGHT / 2 + 50, 0x00FF00, "Press R to restart");
	return (0);
}

int game_start(t_game *game)
{
	game->funct(game);
}
