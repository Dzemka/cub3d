#include <cub3d.h>

static void game_base_init(t_game *game)
{
	game->tex_count = 12;
	game->map = NULL;
	game->mlx = NULL;
	game->window = NULL;
	game->buffer = NULL;
	game->texture = NULL;
	game->tex_img = NULL;
}

static int init_buffer(t_game *game)
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

static int init_sprites(t_game *game)
{
	int i;

	game->sprite = malloc(sizeof(t_sprite *) * 9);
	if (!game->sprite)
		return (1);
	i = -1;
	while (++i < 9)
	{
		game->sprite[i] = malloc(sizeof(t_sprite *));
		if (!game->sprite[i])
			return (1);
	}
	game->zBuffer = malloc(sizeof(int) * WIDTH);
	if (!game->zBuffer)
		return (1);
	return (0);
}

static int init_textures(t_game *game)
{
	int tex_id;

	game->tex_img = malloc(sizeof(t_data_img *) * (TEX_COUNT + 1));
	game->texture = malloc(sizeof(int *) * (TEX_COUNT + 1));
	if (!game->texture)
		return (1);
	tex_id = -1;
	while (++tex_id < TEX_COUNT)
	{
		game->tex_img[tex_id] = malloc(sizeof(t_data_img));
		if (!game->tex_img[tex_id])
			return (1);
	}
}

int init_memory(t_game *game)
{
	game_base_init(game);

	if (init_buffer(game) == 1)
		game_clean(&game);
	if (init_textures(game) == 1)
		game_clean(&game);
	if (init_sprites(game) == 1)
		game_clean(&game);
	game->map = malloc(sizeof(t_map));
	if (!game->map)
		return (parse_error_message("Malloc error\n", -1));
	game->map->path_textures = malloc(sizeof(char *) * (TEX_COUNT + 1));
	if (!game->map->path_textures)
		return (1);
	game->map->path_textures[12] = NULL;
}
