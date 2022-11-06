#include <cub3d.h>

int main(int argc, char **argv)
{
	t_game *game;

	game = init_game(argc, argv);

	// mlx_mouse_hide(game->mlx, game->window);
	mlx_mouse_hide();
	// mlx_mouse_move(game->mlx, game->window, WIDTH / 2, HEIGHT / 2);
	mlx_mouse_move(game->window, WIDTH / 2, HEIGHT / 2);
	game_start(game);
	hooks(game);
	mlx_loop(game->mlx);
	return (0);
}
