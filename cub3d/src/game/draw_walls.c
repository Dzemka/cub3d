#include <cub3d.h>
void get_tex_num(t_wall_verline *verline, t_game *game)
{
	if (verline->ray.side == 0)
	{
		if (verline->ray.dir.x < 0)
			verline->texNum = 2;
		else
			verline->texNum = 3;
	}
	else
	{
		if (verline->ray.dir.y < 0)
			verline->texNum = 0;
		else
			verline->texNum = 1;
	}
}

double get_tex_x(t_wall_verline *verline, t_game *game)
{
	double wallX;

	if (verline->ray.side == 0)
		wallX = game->player->pos.y + verline->perpWallDist * verline->ray.dir.y;
	else
		wallX = game->player->pos.x + verline->perpWallDist * verline->ray.dir.x;
	wallX -= floor(wallX);
	verline->texX = (int)(wallX * (double)(game->tex_img[verline->texNum]->width));
}

void fill_verline(int texNum, int texX, int lineHeight, t_game *game, int x, t_wall_verline *verline)
{
	verline->drawStart -= 1;
	while (++verline->drawStart < verline->drawEnd)
	{
		game->buffer[verline->drawStart][x] = game->texture[texNum][(int)verline->texY][texX]; //сделать чтобы использовались текстуры разных разрешений
		verline->texY += verline->step;
	}
}

void get_data_iter(t_wall_verline *verline, t_game *game)
{
	verline->lineHeight = (int)(HEIGHT / verline->perpWallDist);
	verline->step = (double)game->tex_img[verline->texNum]->height / (double)verline->lineHeight;
	verline->drawStart = HEIGHT / 2 - verline->lineHeight / 2 + game->pitch;
	verline->texY = 0;
	if (verline->drawStart < 0)
	{
		verline->texY = verline->drawStart * verline->step * -1;
		verline->drawStart = 0;
	}
	verline->drawEnd = HEIGHT / 2 + verline->lineHeight / 2 + game->pitch;
	if (verline->drawEnd >= HEIGHT)
		verline->drawEnd = HEIGHT - 1;
}

void draw_walls(t_game *game)
{
	t_wall_verline verline;
	int x;

	x = -1;
	while (++x < WIDTH)
	{
		verline.x = x;
		get_perp_wall_dist(&verline, game);
		get_tex_num(&verline, game);
		get_tex_x(&verline, game);
		get_data_iter(&verline, game);
		fill_verline(verline.texNum, verline.texX, verline.lineHeight, game, x, &verline);
		game->zBuffer[x] = verline.perpWallDist;
	}
}
