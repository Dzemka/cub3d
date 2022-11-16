#include <cub3d.h>

static void do_damage(t_game *game)
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
						game->enemy[game->map->map_grid[pos_y + row][pos_x + col] - 48 - 6]->health -= PLAYER_DAMAGE;
				}
			}
		}
	}
}

static void attack_animation(t_game *game)
{
	game->player.frame++;
	if (game->player.weapon_action < 2)
		game->player.weapon_action = 3;
	if (game->player.frame % 5 == 0)
		game->player.weapon_action++;
	if (game->player.frame == 100)
		game->player.frame = 0;
	if (game->player.weapon_action == 11)
	{
		game->player.weapon_action = 0;
		game->player.attack = 0;
		do_damage(game);
	}
}

static void standart_animation(t_game *game)
{
	game->player.frame++;
	if (game->player.frame % 8 == 0)
		game->player.weapon_action++;
	if (game->player.frame == 100)
		game->player.frame = 0;
	if (game->player.weapon_action == 3)
		game->player.weapon_action = 0;
}

static void fill_buffer(double step_x, double step_y, double start_x, t_game *game)
{
	int x;
	int y;
	double texX;
	double texY;

	texY = 0;
	y = HEIGHT / 2;
	while (++y < HEIGHT)
	{
		x = -1;
		texX = start_x;
		while (++x < WIDTH)
		{
			if (game->weapon_tex[(int)texY][(int)texX] != 16777216)
				game->buffer[y][x] = game->weapon_tex[(int)texY][(int)texX];
			texX += step_x;
		}
		texY += step_y;
	}
}

void draw_weapon(t_game *game)
{
	double step_x;
	double step_y;
	double start_x;

	if (game->player.attack == 1)
		attack_animation(game);
	else
		standart_animation(game);
	step_x = (double)(game->weapon_img.width - 1) / WIDTH / 11;
	step_y = (double)(game->weapon_img.height - 1) / HEIGHT * 2;
	start_x = game->weapon_img.width / 11 * game->player.weapon_action;
	fill_buffer(step_x, step_y, start_x, game);
}
