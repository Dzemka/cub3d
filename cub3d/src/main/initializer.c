#include <cub3d.h>

static int init_map(t_map **map, int argc, char **argv)
{
	int map_fd;

	map_fd = open(argv[1], O_RDONLY);
	if (map_fd == -1)
	{
		perror(argv[1]);
		return (1);
	}
	*map = malloc(sizeof(t_map));
	if (!*map)
		return (parse_error_message("Malloc error\n", -1));
	init_values(*map);
	(*map)->path_textures = malloc(sizeof(char *) * (4 + 1));
	if (!(*map)->path_textures)
		return(1);
	(*map)->path_textures[4] = NULL;
	if (parse_map(*map, map_fd) == 1)
		return (1);
	return (0);
}

static void player_init(t_game *game)
{
	if (game->map->player_orientation == 'N')
	{
		fill_coord(-1, 0, &game->player.dir);
		fill_coord(0, 0.66, &game->player.plane);
	}
	else if (game->map->player_orientation == 'W')
	{
		fill_coord(0, -1, &game->player.dir);
		fill_coord(-0.66, 0, &game->player.plane);
	}
	else if (game->map->player_orientation == 'S')
	{
		fill_coord(1, 0, &game->player.dir);
		fill_coord(0, -0.66, &game->player.plane);
	}
	else if (game->map->player_orientation == 'E')
	{
		fill_coord(0, 1, &game->player.dir);
		fill_coord(0.66, 0, &game->player.plane);
	}
	printf("%f %f\n", game->map->player_p.x, game->map->player_p.y);
	fill_coord(game->map->player_p.y + 0.5, game->map->player_p.x + 0.5, &game->player.pos);
	game->map->map_grid[(int)game->map->player_p.y][(int)game->map->player_p.x] = '0';
}

static int init_graphic(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return(1);
	game->window = mlx_new_window(game->mlx, WIDTH, HEIGHT, "game");
	if (!game->window)
		return(1);
	game->img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp, &game->img.line_length, &game->img.endian);
	game->wall_color = 0x00FFFF;
	return (0);
}

static void	game_base_init(t_game *game)
{
	game->tex_count = 4;
	game->map = NULL;
	game->mlx = NULL;
	game->window = NULL;
	game->buffer = NULL;
	game->texture = NULL;
	game->tex_img = NULL;
}

t_game *game_init(int argc, char **argv)
{
	t_game *game;

	if (argc != 2)
	{
		printf("The number of arguments must be equal to two\n");
		exit(1);
	}
	game = malloc(sizeof(t_game));
	if (!game)
	{
		printf("Malloc error\n");
		exit(errno);
	}
	game_base_init(game);
	if (init_map(&game->map, argc, argv) == 1)
		return(game_clean(&game));
	player_init(game);
	if (init_graphic(game) == 1)
		return(game_clean(&game));
	if (get_buffer(game) == 1)
		return(game_clean(&game));
	if (get_textures(game) == 1)
		return(game_clean(&game));
	if (get_sprites(game) == 1)
		return(game_clean(&game));

	//test
	game->pitch = 0;
	game->posZ = 0;
	//test
	return (game);
}
