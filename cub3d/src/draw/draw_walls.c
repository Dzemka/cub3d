/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <olugash@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 06:29:10 by olugash           #+#    #+#             */
/*   Updated: 2022/11/18 08:21:30 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	get_tex_num(t_wall_verline *verline)
{
	if (verline->ray.side == 0)
	{
		if (verline->ray.dir.x < 0)
			verline->texnum = 2;
		else
			verline->texnum = 3;
	}
	else if (verline->ray.side == 1)
	{
		if (verline->ray.dir.y < 0)
			verline->texnum = 0;
		else
			verline->texnum = 1;
	}
	else
		verline->texnum = 12;
}

static void	get_tex_x(t_wall_verline *verline, t_game *game)
{
	double	wall_x;

	if (verline->ray.side == 0 || verline->ray.side == 2)
		wall_x = game->player.pos.y
			+ verline->perpwalldist * verline->ray.dir.y;
	else
		wall_x = game->player.pos.x
			+ verline->perpwalldist * verline->ray.dir.x;
	wall_x -= floor(wall_x);
	verline->tex_x = (int)(wall_x
			* (double)(game->tex_img[verline->texnum]->width));
}

static void	fill_verline(t_game *game, t_wall_verline *verline)
{
	verline->drawstart -= 1;
	while (++verline->drawstart < verline->drawend)
	{
		game->buffer[verline->drawstart][verline->x]
			= game
			->texture[verline->texnum][(int)verline->tex_y][verline->tex_x];
		verline->tex_y += verline->step;
	}
}

static void	get_data_iter(t_wall_verline *verline, t_game *game)
{
	verline->lineheight = (int)(HEIGHT / verline->perpwalldist);
	verline->step = ((double)game->tex_img[verline->texnum]->height - 1)
		/ (double)verline->lineheight;
	verline->drawstart = HEIGHT / 2 - verline->lineheight / 2 + game->pitch;
	verline->tex_y = 0;
	if (verline->drawstart < 0)
	{
		verline->tex_y = verline->drawstart * verline->step * -1;
		verline->drawstart = 0;
	}
	verline->drawend = HEIGHT / 2 + verline->lineheight / 2 + game->pitch;
	if (verline->drawend >= HEIGHT)
		verline->drawend = HEIGHT - 1;
}

void	draw_walls(t_game *game)
{
	t_wall_verline	verline;
	int				x;

	x = -1;
	door_update(game);
	while (++x < WIDTH)
	{
		verline.x = x;
		get_perp_wall_dist(&verline, game);
		get_tex_num(&verline);
		get_tex_x(&verline, game);
		get_data_iter(&verline, game);
		fill_verline(game, &verline);
		game->zbuffer[x] = verline.perpwalldist;
	}
}
