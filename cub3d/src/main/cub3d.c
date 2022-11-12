#include <cub3d.h>

int main(int argc, char **argv)
{
	t_game *game;

	game = init_game(argc, argv);

	hooks(game);
	mlx_loop(game->mlx);
	return (0);
}
