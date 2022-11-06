#include <cub3d.h>

static int get_graphic(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (1);
	game->window = mlx_new_window(game->mlx, WIDTH, HEIGHT, "game");
	if (!game->window)
		return (1);
	game->img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp, &game->img.line_length, &game->img.endian);
	return (0);
}

static int init_buffer(t_game *game)
{
	int y;

	y = -1;
	game->buffer = malloc(sizeof(int *) * HEIGHT + 1);
	if (!game->buffer)
		game_exit("Malloc error\n");
	while (++y < HEIGHT)
	{
		game->buffer[y] = malloc(sizeof(int *) * WIDTH);
		if (!game->buffer[y])
			game_exit("Malloc error\n");
	}
	game->buffer[y + 1] = NULL;
}

static void init_player(t_game *game)
{
	game->player = malloc(sizeof(t_player));
	if (!game->player)
		game_exit("Malloc_error");
	game->player->dir = malloc(sizeof(t_coord));
	game->player->plane = malloc(sizeof(t_coord));
	if (!game->player->dir || !game->player->plane)
		game_exit("Malloc error\n");
	if (game->map->player_orientation == 'N')
	{
		fill_coord(-1, 0, game->player->dir);
		fill_coord(0, 0.66, game->player->plane);
	}
	else if (game->map->player_orientation == 'W')
	{
		fill_coord(0, -1, game->player->dir);
		fill_coord(-0.66, 0, game->player->plane);
	}
	else if (game->map->player_orientation == 'S')
	{
		fill_coord(1, 0, game->player->dir);
		fill_coord(0, -0.66, game->player->plane);
	}
	else if (game->map->player_orientation == 'E')
	{
		fill_coord(0, 1, game->player->dir);
		fill_coord(0.66, 0, game->player->plane);
	}
	game->player->pos = malloc(sizeof(t_coord));
	fill_coord(game->map->player_p->y + 0.5, game->map->player_p->x + 0.5, game->player->pos);
	int i;
	i = 0;
	game->map->map_grid[(int)game->map->player_p->y][(int)game->map->player_p->x] = '0';
}

t_game *init_game(int argc, char **argv)
{
	t_game *game;

	if (argc != 2)
		game_exit("The number of arguments must be equal to two");
	game = malloc(sizeof(t_game));
	if (!game)
		game_exit("Malloc error\n");
	init_map(game, argc, argv);
	get_graphic(game);
	init_textures(game);
	init_player(game);
	init_buffer(game);
	game->pitch = 0;
	game->posZ = 0;
	return (game);
}
