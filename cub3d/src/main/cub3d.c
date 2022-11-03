#include <cub3d.h>

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
	//new
	init_memory(game);
	init_values(argc, argv, game);
	//new
	// test
	game->pitch = 0;
	game->posZ = 0;
	// test
	return (game);
}

int main(int argc, char **argv)
{
	t_game *game;

	game = game_init(argc, argv);
	// t_list *list;
	// t_coord *coord;

	// list = game->sprite[1]->pos;
	// coord = list->content;
	// printf("%f %f\n", coord->x, coord->y);
	mlx_mouse_hide(game->mlx, game->window);
	mlx_mouse_move(game->mlx, game->window, WIDTH / 2, HEIGHT / 2);
	game_start(game);
	hooks(game);
	mlx_loop(game->mlx);
	return (0);
}
