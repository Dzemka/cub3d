#include <cub3d.h>

int main(int argc, char **argv)
{
	t_game *game;

	game = game_init(argc, argv);

	game_start(game);
	hooks(game);
	mlx_loop(game->mlx);
	return (0);
}
