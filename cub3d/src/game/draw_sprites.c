#include <cub3d.h>

void draw_sprites(t_game *game)
{
	int sprite_order[2];

	double sprite_dist[2];

	int i;

	i = 0;

	// while (++i < 2)
	// {
	// 	sprite_order[i] = i;
	// 	sprite_dist[i] = ((game->player.pos.x - game->sprite[i]->pos.x) * (game->player.pos.x - game->sprite[i]->pos.x) + (game->player.pos.y - game->sprite[i]->pos.y) * (game->player.pos.y - game->sprite[i]->pos.y));
	// }
	// if (sprite_dist[1] < sprite_dist[0])
	// {
	// 	sprite_order[1] = 0;
	// 	sprite_order[0] = 1;
	// }
	// sorting

	double inv_det;
	t_coord transform;

	int sprite_screen_x;

	int sprite_height;

	int sprite_width;

	int drawStartX;
	int drawEndX;
	int drawStartY;
	int drawEndY;

	int texX;
	double texY;
	int y;

	int stripe;

	int d;

	t_coord sprite;
	int color;
	fill_coord(3.5, 12.5, &game->sprite[0]->pos);
	fill_coord(5.5, 10.5, &game->sprite[1]->pos);
	i = -1;
	double step_y;
	double start_y;
	while (++i < 2)
	{
		sprite_dist[i] = (game->player.pos.x - game->sprite[i]->pos.x) * (game->player.pos.x - game->sprite[i]->pos.x) + (game->player.pos.y - game->sprite[i]->pos.y) * (game->player.pos.y - game->sprite[i]->pos.y);

		// translate sprite position relative camera

		// do order
		fill_coord(game->sprite[i]->pos.y - game->player.pos.y, game->sprite[i]->pos.x - game->player.pos.x, &sprite); // coordinate ratio player
		// do order

		//[plane.x dir.x] -1												[dir.y 	   -dir.x]
		//[				]		= 1 / (plane.x * dir.y - dir.x * plane.y) * [			 	 ]
		//[plane.y dir.y]													[-plane.y plane.x]
		// determinant matrix

		// printf("matrix x: %f %f\nmartix y: %f %f\n", game->player.plane.x, game->player.dir.x, game->player.plane.y, game->player.dir.y);
		inv_det = 1.0 / (game->player.plane.x * game->player.dir.y - game->player.dir.x * game->player.plane.y);
		// matrix * vector
		//[sprite.x	]		[dir.y		-dir.x	]
		//[			] * det [					]
		//[sprite.y ]		[-plane.y	plane.x	]
		transform.x = inv_det * (game->player.dir.y * sprite.x - game->player.dir.x * sprite.y);			//
																											// multiplication matrix pos sprite to inverse matix for get cross point
		transform.y = inv_det * ((game->player.plane.y * -1) * sprite.x + game->player.plane.x * sprite.y); //
		sprite_screen_x = (int)((WIDTH / 2) * (1.0 + transform.x / transform.y));							// coordinate sprite on cameraX

		sprite_height = abs((int)((double)HEIGHT / (transform.y))); // height of sprite on monitor plane
		drawStartY = -sprite_height / 2 + HEIGHT / 2;
		drawEndY = sprite_height / 2 + HEIGHT / 2;
		if (drawStartY < 0)
			drawStartY = 0;
		if (drawEndY >= HEIGHT)
			drawEndY = HEIGHT - 1;
		sprite_width = abs((int)(HEIGHT / (transform.y))); // width of sprite on monitor plane
		// printf("%d\n", sprite_height);
		drawStartX = -sprite_width / 2 + sprite_screen_x;
		drawEndX = sprite_width / 2 + sprite_screen_x;
		if (drawStartX < 0)
			drawStartX = 0;
		if (drawEndX >= WIDTH)
			drawEndX = WIDTH - 1;
		stripe = drawStartX;
		step_y = (double)(TEX_HEIGHT - 1) / (double)sprite_height;

		start_y = 0;
		if (sprite_height > HEIGHT)
			start_y = ((sprite_height - HEIGHT) / 2) * step_y;
		if (stripe < WIDTH && stripe >= 0)
		{
			while (stripe < drawEndX)
			{
				texY = start_y;

				if (transform.y > 0 && stripe > 0 && stripe < WIDTH && transform.y < game->zBuffer[stripe])
				{
					texX = (int)((stripe - (sprite_screen_x - sprite_width / 2)) * TEX_WIDTH / sprite_width);
					y = drawStartY;
					while (y < drawEndY)
					{
						// d = (y) * 2 - HEIGHT + sprite_height;
						// texY = ((d * TEX_HEIGHT) / sprite_height) / 2;
						color = game->sprite_tex[i][(int)texY][texX];
						if (color != 16777216)
							game->buffer[y][stripe] = color;
						y++;
						texY += step_y;
					}
				}
				stripe++;
			}
		}
	}
	y = -1;
	int x;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			ft_pixel_put(&game->img, x, y, game->buffer[y][x]);
		}
	}
}
