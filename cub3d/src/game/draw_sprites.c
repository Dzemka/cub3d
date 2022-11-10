#include <cub3d.h>

static void	get_draw_data(int i, t_sprite_draw *draw_data, t_game *game)
{
	t_coord	transform;
	double	inv_det;
	t_coord	sprite;
	int		sprite_screen_x;

	fill_coord(game->sprite[i]->coord->y - game->player->pos->y, game->sprite[i]->coord->x - game->player->pos->x, &sprite);
	inv_det = 1.0 / (game->player->plane->x * game->player->dir->y - game->player->dir->x * game->player->plane->y);
	transform.x = inv_det * (game->player->dir->y * sprite.x - game->player->dir->x * sprite.y);
	transform.y = inv_det * ((game->player->plane->y * -1) * sprite.x + game->player->plane->x * sprite.y);
	draw_data->sprite_height = abs((int)((double)HEIGHT / (transform.y)));
	draw_data->sprite_width = abs((int)(HEIGHT / (transform.y)));
	sprite_screen_x = (int)((WIDTH / 2) * (1.0 + transform.x / transform.y));
	draw_data->drawStartY = -draw_data->sprite_height / 2 + HEIGHT / 2 + game->pitch;
	draw_data->drawEndY = draw_data->sprite_height / 2 + HEIGHT / 2 + game->pitch;
	if (draw_data->drawEndY >= HEIGHT)
		draw_data->drawEndY = HEIGHT - 1;
	draw_data->drawStartX = -draw_data->sprite_width / 2 + sprite_screen_x;
	draw_data->drawEndX = sprite_screen_x + draw_data->sprite_width / 2;
	if (draw_data->drawEndX >= WIDTH)
		draw_data->drawEndX = WIDTH - 1;
	draw_data->draw_distance = transform.y;
	draw_data->tex_id = game->sprite[i]->id;
	draw_data->step_y = (double)(game->tex_img[draw_data->tex_id]->height - 1) / (double)draw_data->sprite_height;
	draw_data->step_x = (double)game->tex_img[draw_data->tex_id]->width / (double)draw_data->sprite_width;
}

static void	get_draw_start(int *start_tex_y, double *texX, t_sprite_draw *draw_data)
{
	*start_tex_y = 0;
	if (draw_data->drawStartY < 0)
	{
		*start_tex_y = draw_data->step_y * draw_data->drawStartY * -1;
		draw_data->drawStartY = 0;
	}
	*texX = 0;
	if (draw_data->drawStartX < 0)
	{
		*texX = (double)draw_data->drawStartX * -1 * draw_data->step_x;
		draw_data->drawStartX = 0;
	}
}

static void	sprite_to_buffer(t_sprite_draw *draw_data, t_game *game)
{
	double texX;
	double texY;
	int		y;
	int		start_tex_y;

	get_draw_start(&start_tex_y, &texX, draw_data);
	while (draw_data->drawStartX < draw_data->drawEndX)
	{
		texY = start_tex_y;
		y = draw_data->drawStartY;
		if (draw_data->draw_distance >= 0 && draw_data->drawStartX > 0 && draw_data->drawStartX < WIDTH && draw_data->draw_distance < game->zBuffer[draw_data->drawStartX])
		{
			while (y < draw_data->drawEndY)
			{
				if (game->texture[draw_data->tex_id][(int)texY][(int)texX] != 16777216)
					game->buffer[y][draw_data->drawStartX] = game->texture[draw_data->tex_id][(int)texY][(int)texX];
				y++;
				texY += draw_data->step_y;
			}
		}
		texX += draw_data->step_x;
		draw_data->drawStartX++;
	}
}

void draw_sprites(t_game *game)
{
	t_sprite_draw	draw_data;
	int				i;

	set_sprite_order(game);
	i = -1;
	while (++i < game->map->sprite_count)
	{
		get_draw_data(i, &draw_data, game);
		sprite_to_buffer(&draw_data, game);
	}
}
