#include <cub3d.h>

int move(int keycode, void *arg)
{
	t_game *game;
	t_coord new_pos;
	double move_speed = 0.15;
	double rotate_speed;
	double oldDirX;
	double oldPlaneX;

	double move_dir_x;
	double move_dir_y;

	char c;
	game = (t_game *)arg;
	if (keycode == KEY_ESC)
	{
		exit(1);
		game_clean(&game);
	}
	if (keycode == KEY_W)
	{
		c = game->map->map_grid[(int)game->player.pos.y][(int)(game->player.pos.x + game->player.dir.x * move_speed)];
		if (c == '0' || (c > 5 + 48))
			game->player.pos.x += game->player.dir.x * move_speed;
		c = game->map->map_grid[(int)(game->player.pos.y + game->player.dir.y * move_speed)][(int)(game->player.pos.x)];
		if (c == '0' || (c > 5 + 48))
			game->player.pos.y += game->player.dir.y * move_speed;
	}
	if (keycode == KEY_S)
	{
		c = game->map->map_grid[(int)game->player.pos.y][(int)(game->player.pos.x - game->player.dir.x * move_speed)];
		if (c == '0' || (c > 5 + 48))
			game->player.pos.x -= game->player.dir.x * move_speed;
		c = game->map->map_grid[(int)(game->player.pos.y - game->player.dir.y * move_speed)][(int)(game->player.pos.x)];
		if (c == '0' || (c > 5 + 48))
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
		c = game->map->map_grid[(int)game->player.pos.y][(int)(game->player.pos.x + move_dir_x * move_speed)];
		if (c == '0' || (c > 5 + 48))
			game->player.pos.x += move_dir_x * move_speed;
		c = game->map->map_grid[(int)(game->player.pos.y + move_dir_y * move_speed)][(int)game->player.pos.x];
		if (c == '0' || (c > 5 + 48))
			game->player.pos.y += move_dir_y * move_speed;
	}
	if (keycode == KEY_DOWN)
	{
		game->pitch -= 400 * move_speed;
		if (game->pitch < -400)
			game->pitch = -400;
	}
	if (keycode == KEY_UP)
	{
		game->pitch += 400 * move_speed;
		if (game->pitch > 400)
			game->pitch = 400;
	}
	if (keycode == KEY_R)
		get_start(game);
}

int mouse_move(int x, int y, t_game *game)
{
	double move_dir_x;
	double move_dir_y;
	double move_speed;
	double rotate_speed;
	double oldDirX;
	double oldPlaneX;

	rotate_speed = 0;
	move_speed = 50.0 / HEIGHT;
	if (x < WIDTH / 2)
		rotate_speed = 50.0 / WIDTH;
	if (x > WIDTH / 2)
		rotate_speed = -(50.0 / WIDTH);
	if (y > HEIGHT / 2)
		game->pitch -= 400 * move_speed;
	if (game->pitch < -400)
		game->pitch = -400;
	if (y < HEIGHT / 2)
		game->pitch += 400 * move_speed;
	if (game->pitch > 400)
		game->pitch = 400;
	oldDirX = game->player.dir.x;
	game->player.dir.x = game->player.dir.x * cos(-rotate_speed) - game->player.dir.y * sin(-rotate_speed);
	game->player.dir.y = oldDirX * sin(-rotate_speed) + game->player.dir.y * cos(-rotate_speed);
	oldPlaneX = game->player.plane.x;
	game->player.plane.x = game->player.plane.x * cos(-rotate_speed) - game->player.plane.y * sin(-rotate_speed);
	game->player.plane.y = oldPlaneX * sin(-rotate_speed) + game->player.plane.y * cos(-rotate_speed);
	mlx_mouse_move(game->window, WIDTH / 2, HEIGHT / 2);
	// mlx_mouse_move(game->mlx, game->window, WIDTH / 2, HEIGHT / 2);
}

int mouse_press(int button, int x, int y, t_game *game)
{
	int pos_x;
	int pos_y;
	int row;
	int col;

	pos_x = (int)(game->player.pos.x);
	pos_y = (int)(game->player.pos.y);

	row = -3;
	while (++row <= 2)
	{
		col = -3;
		while (++col <= 2)
		{
			if (pos_y + row > 0 && pos_y < game->map->height && pos_x + col > 0 && pos_x)
			{
				if (pos_x + col < ft_strlen(game->map->map_grid[pos_y + row]))
				{
					if (ft_strchr("6789", game->map->map_grid[pos_y + row][pos_x + col]))
						game->enemy[game->map->map_grid[pos_y + row][pos_x + col] - 48 - 6]->health -= 50;
				}
			}
		}
	}
}
void hooks(t_game *game)
{
	mlx_hook(game->window, 4, 1L << 2, &mouse_press, game);
	mlx_hook(game->window, 6, 1L << 6, &mouse_move, game);
	mlx_hook(game->window, 2, 1L << 0, &move, game);
	mlx_loop_hook(game->mlx, &game_start, game);
}
