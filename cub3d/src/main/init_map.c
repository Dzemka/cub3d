#include <cub3d.h>

static int	get_fd(char *s)
{
    int fd;

    fd = open(s, O_RDONLY);
    if (fd == -1)
    {
        perror(s);
        exit (errno);
    }
    return (fd);
}

static void	init_map_values(t_map *map)
{
	map->floor_color = -1;
	map->ceiling_color = -1;
	map->map_grid = NULL;
	map->lineList = NULL;
	map->width = 0;
	map->player_orientation = '\0';
	map->sprite_count = 0;
	map->grid_ptr = NULL;
}

static void	map_data_malloc(t_game *game)
{
	int	i;

	game->map = malloc(sizeof(t_map));
	if (!game->map)
		game_exit("Malloc error\n");
	init_map_values(game->map);
	game->map->game = game;
	game->map->path_textures = malloc(sizeof(char *) * (TEX_COUNT + 1));
	if (!game->map->path_textures)
		game_exit("Malloc error\n");
	i = -1;
	while (++i <= TEX_COUNT)
		game->map->path_textures[i] = NULL;
}

void	init_map(t_game *game, int argc, char **argv)
{
    int map_fd;

	map_data_malloc(game);
    map_fd = get_fd(argv[1]);
    parse_map(game, map_fd);
	close(map_fd);
}
