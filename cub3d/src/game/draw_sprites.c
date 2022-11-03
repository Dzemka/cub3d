#include <cub3d.h>

void draw_sprites(t_game *game)
{
	int sprite_order[2];

	double sprite_dist[2];

	int i;

	i = 0;

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
	// fill_coord(3.5, 12.5, &game->sprite[0]->pos);
	// fill_coord(5.5, 10.5, &game->sprite[1]->pos);
	i = -1;
	double step_y;
	double start_y;

	t_coord *coord;
	while (++i < 6)
	{
		coord = (t_coord *)game->sprite[i]->pos->content;
		// sprite_dist[i] = game->player.pos.x - coord->x * (game->player.pos.x - coord->x) + (game->player.pos.y - coord->y) * (game->player.pos.y - coord->y);

		// translate sprite position relative camera

		// do order
		fill_coord(coord->y - game->player.pos.y, coord->x - game->player.pos.x, &sprite); // coordinate ratio player
		// do order

		//[plane.x dir.x] -1												[dir.y 	   -dir.x]
		//[				]		= 1 / (plane.x * dir.y - dir.x * plane.y) * [			 	 ]
		//[plane.y dir.y]													[-plane.y plane.x]
		// determinant matrix

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
		drawStartY = -sprite_height / 2 + HEIGHT / 2 + game->pitch;
		drawEndY = sprite_height / 2 + HEIGHT / 2 + game->pitch;
		if (drawEndY >= HEIGHT)
			drawEndY = HEIGHT - 1;
		sprite_width = abs((int)(HEIGHT / (transform.y))); // width of sprite on monitor plane
		drawStartX = -sprite_width / 2 + sprite_screen_x;
		drawEndX = sprite_width / 2 + sprite_screen_x;
		if (drawStartX < 0)
			drawStartX = 0;
		if (drawEndX >= WIDTH)
			drawEndX = WIDTH - 1;
		stripe = drawStartX;
		step_y = (double)(game->tex_img[i + 4]->height - 1) / (double)sprite_height;
		start_y = 0;
		if (stripe < WIDTH && stripe >= 0)
		{
			y = drawStartY;
			if (y < 0)
			{
				start_y = step_y * y * -1;
				drawStartY = 0;
			}
			while (stripe < drawEndX)
			{
				texY = start_y;
				if (transform.y > 0 && stripe > 0 && stripe < WIDTH && transform.y < game->zBuffer[stripe])
				{
					texX = (int)((stripe - (sprite_screen_x - sprite_width / 2)) * game->tex_img[i + 4]->width / sprite_width);
					y = drawStartY;
					while (y < drawEndY)
					{
						color = game->texture[i + 4][(int)texY][texX];
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
}