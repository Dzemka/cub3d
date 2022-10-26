#include <cub3d.h>

int move(int keycode, void *arg)
{
	t_game *game;
	t_coord new_pos;
	double move_speed = 0.1;
	double rotate_speed;
	double oldDirX;
	double oldPlaneX;

	double move_dir_x;
	double move_dir_y;

	game = (t_game *)arg;
	if (keycode == KEY_ESC)
	{
		game_clean(&game);
		exit(1);
	}
	if (keycode == KEY_W)
	{
		if (game->map->map_grid[(int)game->player.pos.y][(int)(game->player.pos.x + game->player.dir.x * move_speed)] == '0')
			game->player.pos.x += game->player.dir.x * move_speed;
		if (game->map->map_grid[(int)(game->player.pos.y + game->player.dir.y * move_speed)][(int)(game->player.pos.x)] == '0')
			game->player.pos.y += game->player.dir.y * move_speed;
	}
	if (keycode == KEY_S)
	{
		if (game->map->map_grid[(int)game->player.pos.y][(int)(game->player.pos.x - game->player.dir.x * move_speed)] == '0')
			game->player.pos.x -= game->player.dir.x * move_speed;
		if (game->map->map_grid[(int)(game->player.pos.y - game->player.dir.y * move_speed)][(int)(game->player.pos.x)] == '0')
			game->player.pos.y -= game->player.dir.y * move_speed;
	}
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
	{
		rotate_speed = 0.1;
		if (keycode == KEY_RIGHT)
			rotate_speed *= -1;
		oldDirX = game->player.dir.x;
		game->player.dir.x = game->player.dir.x * cos(-rotate_speed) - game->player.dir.y * sin(-rotate_speed);
		game->player.dir.y = oldDirX * sin(-rotate_speed) + game->player.dir.y * cos(-rotate_speed);
		oldPlaneX = game->player.plane.x;
		game->player.plane.x = game->player.plane.x * cos(-rotate_speed) - game->player.plane.y * sin(-rotate_speed);
		game->player.plane.y = oldPlaneX * sin(-rotate_speed) + game->player.plane.y * cos(-rotate_speed);
	}
	if (keycode == KEY_D || keycode == KEY_A)
	{
		if (keycode == KEY_D)
			rotate_speed = 1.5708;
		else
			rotate_speed = -1.5708;
		move_dir_x = game->player.dir.x * cos(rotate_speed) - game->player.dir.y * sin(rotate_speed);
		move_dir_y = game->player.dir.x * sin(rotate_speed) + game->player.dir.y * cos(rotate_speed);
		if (game->map->map_grid[(int)game->player.pos.y][(int)(game->player.pos.x + move_dir_x * move_speed + move_dir_x * 0.1)] == '0')
			game->player.pos.x += move_dir_x * move_speed;
		if (game->map->map_grid[(int)(game->player.pos.y + move_dir_y * move_speed + move_dir_y * 0.1)][(int)game->player.pos.x] == '0')
			game->player.pos.y += move_dir_y * move_speed;		
	}
	if (keycode == KEY_DOWN)
	{
		game->pitch -= 400 * move_speed;
		if (game->pitch < -400)
			game->pitch = -400;
		// game->posZ = 200;
	}
	if (keycode == KEY_UP)
	{
		game->pitch += 400 * move_speed;
		if (game->pitch > 400)
			game->pitch = 400;
		// game->posZ = -200;
	}
	// draw_basic(game);
	// draw_floor(game);
	// draw_walls(game);
	// draw_sprites(game);
	game_start(game);
	// mlx_put_image_to_window(game->mlx, game->window, game->img.img, 0, 0);
}

void hooks(t_game *game)
{
	mlx_hook(game->window, 2, 1L << 0, &move, game);
}
