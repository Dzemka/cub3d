/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <olugash@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 05:52:43 by olugash           #+#    #+#             */
/*   Updated: 2022/11/18 08:21:41 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	get_draw_begins(t_game *game, t_sprite_draw *draw_data,
	int sprite_screen_x)
{
	draw_data->drawstart_y = HEIGHT / 2 - draw_data->sprite_height
		/ 2 + game->pitch;
	draw_data->drawend_y = HEIGHT / 2 + draw_data->sprite_height
		/ 2 + game->pitch;
	draw_data->drawstart_x = sprite_screen_x - draw_data->sprite_width
		/ 2;
	draw_data->drawend_x = sprite_screen_x + draw_data->sprite_width
		/ 2;
}

static void	get_draw_data(int i, t_sprite_draw *draw_data, t_game *game)
{
	t_coord	transform;
	double	inv_det;
	t_coord	sprite;
	int		sprite_screen_x;

	fill_coord(game->sprite[i]->coord.y - game->player.pos.y,
		game->sprite[i]->coord.x - game->player.pos.x, &sprite);
	inv_det = 1.0 / (game->player.plane.x * game->player.dir.y
			- game->player.dir.x * game->player.plane.y);
	transform.x = inv_det * (game->player.dir.y * sprite.x
			- game->player.dir.x * sprite.y);
	transform.y = inv_det * ((game->player.plane.y * -1) * sprite.x
			+ game->player.plane.x * sprite.y);
	draw_data->sprite_height = abs((int)(HEIGHT / (transform.y)));
	draw_data->sprite_width = abs((int)(HEIGHT / (transform.y)));
	sprite_screen_x = (int)((WIDTH / 2) * (1 + transform.x / transform.y));
	get_draw_begins(game, draw_data, sprite_screen_x);
	draw_data->draw_distance = transform.y;
	draw_data->tex_id = game->sprite[i]->id;
	draw_data->step_y = (double)(game->tex_img[draw_data->tex_id]->height - 1)
		/ (double)(draw_data->sprite_height);
	draw_data->step_x = (double)(game->tex_img[draw_data->tex_id]->width - 1)
		/ (double)draw_data->sprite_width;
	draw_data->start_tex_x = 0;
}

static void	get_draw_start(t_sprite_draw *draw_data)
{
	draw_data->start_tex_y = 0;
	if (draw_data->drawstart_y < 0)
	{
		draw_data->start_tex_y = draw_data->step_y
			* draw_data->drawstart_y * -1;
		draw_data->drawstart_y = 0;
	}
	if (draw_data->drawstart_x < 0)
	{
		draw_data->start_tex_x += draw_data->drawstart_x * -1
			* draw_data->step_x;
		draw_data->drawstart_x = 0;
	}
	if (draw_data->drawend_y >= HEIGHT)
		draw_data->drawend_y = HEIGHT - 1;
	if (draw_data->drawend_x >= WIDTH)
		draw_data->drawend_x = WIDTH - 1;
	draw_data->tex_x = draw_data->start_tex_x;
}

static void	sprite_to_buffer(t_sprite_draw *draw_data, t_game *game)
{
	int		y;
	int		color;

	get_draw_start(draw_data);
	while (draw_data->drawstart_x < draw_data->drawend_x)
	{
		draw_data->tex_y = draw_data->start_tex_y;
		y = draw_data->drawstart_y;
		if (draw_data->draw_distance >= 0 && draw_data->drawstart_x > 0
			&& draw_data->drawstart_x < WIDTH && draw_data->draw_distance
			< game->zbuffer[draw_data->drawstart_x])
		{
			while (y < draw_data->drawend_y)
			{
				color = game->texture[draw_data->tex_id][(int)draw_data->tex_y]
				[(int)draw_data->tex_x];
				if (color != 16777216)
					game->buffer[y][draw_data->drawstart_x] = color;
				y++;
				draw_data->tex_y += draw_data->step_y;
			}
		}
		draw_data->tex_x += draw_data->step_x;
		draw_data->drawstart_x++;
	}
}

void	draw_sprites(t_game *game)
{
	t_sprite_draw	draw_data;
	int				i;

	set_sprite_order(game);
	i = -1;
	while (++i < game->map->sprite_count)
	{
		get_draw_data(i, &draw_data, game);
		enemy_draw_setting(i, &draw_data, game);
		sprite_to_buffer(&draw_data, game);
	}
}
