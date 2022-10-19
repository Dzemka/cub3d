#include <cub3d.h>

int get_buffer(t_game *game)
{
	int y;

	y = -1;
	game->buffer = malloc(sizeof(int *) * HEIGHT + 1);
	if (!game->buffer)
		return (1);
	while (++y < HEIGHT)
	{
		game->buffer[y] = malloc(sizeof(int *) * WIDTH);
		if (!game->buffer[y])
			return (1);
	}
	game->buffer[y + 1] = NULL;
}

static void set_color(char *addr, int *color)
{
	*color = addr[0];
	*color += addr[1] * 256;
	*color += addr[2] * 256 * 256;
	*color += 256 * 256 * 256;
}

static int get_tex_img(t_game *game)
{
	int tex_id;

	game->tex_img = malloc(sizeof(t_data_img **) * (game->tex_count + 1));
	if (!game->tex_img)
		return (1);
	tex_id = -1;
	while (++tex_id < game->tex_count)
	{
		game->tex_img[tex_id] = malloc(sizeof(t_data_img));
		if (!game->tex_img[tex_id])
			return (1);
		game->tex_img[tex_id]->img = mlx_xpm_file_to_image(game->mlx, game->map->path_textures[tex_id], &game->tex_img[tex_id]->width, &game->tex_img[tex_id]->height);
		if (!game->tex_img[tex_id]->img)
			return (1);
		game->tex_img[tex_id]->addr = mlx_get_data_addr(game->tex_img[tex_id]->img, &game->tex_img[tex_id]->bpp, &game->tex_img[tex_id]->line_length, &game->tex_img[tex_id]->endian);
		if (!game->tex_img[tex_id]->addr)
			return (1);
	}
}

static int fill_texture(t_game *game)
{
	int tex_id;
	int x;
	int y;

	tex_id = -1;

	tex_id = -1;
	while (++tex_id < game->tex_count)
	{
		y = -1;
		while (++y < game->tex_img[tex_id]->height)
		{
			x = -1;
			while (++x < game->tex_img[tex_id]->width)
				set_color(&game->tex_img[tex_id]->addr[y * game->tex_img[tex_id]->line_length + x * 4], &game->texture[tex_id][y][x]);
		}
	}
	return (0);
}

int get_textures(t_game *game)
{
	int y;
	int tex_id;

	game->texture = malloc(sizeof(int *) * (4 + 1));
	tex_id = -1;
	if (get_tex_img(game) == 1)
		return (1);
	while (++tex_id < 4)
	{
		game->texture[tex_id] = malloc(sizeof(int *) * (game->tex_img[tex_id]->height + 1));
		if (!game->texture[tex_id])
			return (1);
		y = -1;
		while (++y < game->tex_img[tex_id]->height)
		{
			game->texture[tex_id][y] = malloc(sizeof(int *) * (game->tex_img[tex_id]->width + 1));
			if (!game->texture[tex_id][y])
				return (1);
		}
		game->texture[tex_id][y] = NULL;
	}
	game->texture[tex_id + 1] = NULL;
	if (fill_texture(game))
		return (1);
}

int get_sprites(t_game *game)
{
	int tex_id;
	int y;
	int x;

	game->sprite_img = malloc(sizeof(t_data_img *) * (2 + 1));

	char str[2][50] = {{"./textures/barrel.xpm"}, {"./textures/pillar.xpm"}};
	tex_id = -1;
	while (++tex_id < 2)
	{
		game->sprite_img[tex_id] = malloc(sizeof(t_data_img));
		game->sprite_img[tex_id]->img = mlx_xpm_file_to_image(game->mlx, str[tex_id], &game->sprite_img[tex_id]->width, &game->sprite_img[tex_id]->height);
		game->sprite_img[tex_id]->addr = mlx_get_data_addr(game->sprite_img[tex_id]->img, &game->sprite_img[tex_id]->bpp, &game->sprite_img[tex_id]->line_length, &game->sprite_img[tex_id]->endian);
	}

	tex_id = -1;

	game->sprite_tex = malloc(sizeof(int *) * 2);
	while (++tex_id < 2)
	{
		y = -1;
		game->sprite_tex[tex_id] = malloc(sizeof(int *) * (game->tex_img[tex_id]->height));
		while (++y < game->sprite_img[tex_id]->height)
			game->sprite_tex[tex_id][y] = malloc(sizeof(int *) * (game->sprite_img[tex_id]->width));
	}
	tex_id = -1;
	while (++tex_id < 2)
	{
		y = -1;

		while (++y < game->sprite_img[tex_id]->height)
		{
			x = -1;
			while (++x < game->sprite_img[tex_id]->width)
				set_color(&game->sprite_img[tex_id]->addr[game->sprite_img[tex_id]->line_length * y + x * 4], &game->sprite_tex[tex_id][y][x]);
		}
	}
	game->sprite = malloc(sizeof(t_sprite *) * 2);
	game->sprite[0] = malloc(sizeof(t_sprite));
	game->sprite[1] = malloc(sizeof(t_sprite));
	game->zBuffer = malloc(sizeof(int) * WIDTH);
	return (0);
}
