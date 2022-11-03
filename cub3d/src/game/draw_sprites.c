#include <cub3d.h>

void get_distance(t_game *game)
{
	int			i;
	t_sprite	*sprite;
	t_coord		*coord;

	i = -1;
	while (++i < game->map->sprite_count)
	{
		sprite = game->sprite[i];
		coord = &sprite->coord;
		sprite->distance = (game->player.pos.x - coord->x) * (game->player.pos.x - coord->x) + (game->player.pos.y - coord->y) * (game->player.pos.y - coord->y);
		sprite->order = 0;
	}

}

void compare_distance(t_sprite *sprite, t_game *game)
{
	int			i;
	t_sprite	*sprite_compare;
	int			order;

	i = -1;
	order = 0;
	while (++i < SPRITE_COUNT - 1)
	{
		printf("%d\n", i);
		sprite_compare = game->sprite[i];
		if (sprite == sprite_compare)
			printf("da\n");
		if (sprite->distance < sprite_compare->distance)
			order++;
		if (sprite->distance == sprite_compare->distance && sprite_compare->order != 0)
			order++;
	}
	sprite->order = order;
}

void sort_sprites(t_game *game)
{
	int			i;

	i = -1;
	while (++i < SPRITE_COUNT)
		compare_distance(game->sprite[i], game);

}

void set_sprite_order(t_game *game)
{
	get_distance(game);
	sort_sprites(game);
	printf("tyt\n");
}

void draw_sprites(t_game *game)
{
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
	double step_y;
	double start_y;
	t_coord *coord;
	t_sprite *sprite_struct;
	t_list *sprite_ptr;

	int order;
	int index;
	i = -1;
	printf("sho\n");
	set_sprite_order(game);
	// while (++i < SPRITE_COUNT)
	// {
	// 	sprite_ptr = game->sprite[i];
	// 	while (sprite_ptr)
	// 	{
	// 		order = ((t_sprite *)sprite_ptr->content)->order;
	// 		printf("er %d\n", order);
	// 		index = ((t_sprite *)game->sprite[order]->content)->id;
	// 		sprite_struct = game->sprite[index]->content;
	// 		coord = &sprite_struct->coord;
	// 		// translate sprite position relative camera

	// 		// do order
	// 		fill_coord(coord->y - game->player.pos.y, coord->x - game->player.pos.x, &sprite); // coordinate ratio player
	// 		// do order

	// 		//[plane.x dir.x] -1												[dir.y 	   -dir.x]
	// 		//[				]		= 1 / (plane.x * dir.y - dir.x * plane.y) * [			 	 ]
	// 		//[plane.y dir.y]													[-plane.y plane.x]
	// 		// determinant matrix

	// 		inv_det = 1.0 / (game->player.plane.x * game->player.dir.y - game->player.dir.x * game->player.plane.y);
	// 		// matrix * vector
	// 		//[sprite.x	]		[dir.y		-dir.x	]
	// 		//[			] * det [					]
	// 		//[sprite.y ]		[-plane.y	plane.x	]
	// 		transform.x = inv_det * (game->player.dir.y * sprite.x - game->player.dir.x * sprite.y);			//
	// 																											// multiplication matrix pos sprite to inverse matix for get cross point
	// 		transform.y = inv_det * ((game->player.plane.y * -1) * sprite.x + game->player.plane.x * sprite.y); //
	// 		sprite_screen_x = (int)((WIDTH / 2) * (1.0 + transform.x / transform.y));							// coordinate sprite on cameraX

	// 		sprite_height = abs((int)((double)HEIGHT / (transform.y))); // height of sprite on monitor plane
	// 		drawStartY = -sprite_height / 2 + HEIGHT / 2 + game->pitch;
	// 		drawEndY = sprite_height / 2 + HEIGHT / 2 + game->pitch;
	// 		if (drawEndY >= HEIGHT)
	// 			drawEndY = HEIGHT - 1;
	// 		sprite_width = abs((int)(HEIGHT / (transform.y))); // width of sprite on monitor plane
	// 		drawStartX = -sprite_width / 2 + sprite_screen_x;
	// 		drawEndX = sprite_width / 2 + sprite_screen_x;
	// 		if (drawStartX < 0)
	// 			drawStartX = 0;
	// 		if (drawEndX >= WIDTH)
	// 			drawEndX = WIDTH - 1;
	// 		stripe = drawStartX;
	// 		step_y = (double)(game->tex_img[index + 4]->height - 1) / (double)sprite_height;
	// 		start_y = 0;
	// 		if (stripe < WIDTH && stripe >= 0)
	// 		{
	// 			y = drawStartY;
	// 			if (y < 0)
	// 			{
	// 				start_y = step_y * y * -1;
	// 				drawStartY = 0;
	// 			}
	// 			while (stripe < drawEndX)
	// 			{
	// 				texY = start_y;
	// 				if (transform.y > 0 && stripe > 0 && stripe < WIDTH && transform.y < game->zBuffer[stripe])
	// 				{
	// 					texX = (int)((stripe - (sprite_screen_x - sprite_width / 2)) * game->tex_img[index + 4]->width / sprite_width);
	// 					y = drawStartY;
	// 					while (y < drawEndY)
	// 					{
	// 						color = game->texture[index + 4][(int)texY][texX];
	// 						if (color != 16777216)
	// 							game->buffer[y][stripe] = color;
	// 						y++;
	// 						texY += step_y;
	// 					}
	// 				}
	// 				stripe++;
	// 			}
	// 		}
	// 		sprite_ptr = sprite_ptr->next;
	// 	}
	// }
}
