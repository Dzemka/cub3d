#include <cub3d.h>

void draw_floor(t_game *game)
{
	t_coord ray_left;
	t_coord ray_right;

	int y;
	y = -1;

	double posZ;

	int p;

	double rowDist;

	int x;

	t_coord floorStep;
	t_coord floor;

	int cellX;
	int cellY;

	int tx;
	int ty;

	int floor_tex;
	int ceil_tex;

	int color;

	double weight;
	fill_coord(game->player.dir.y - game->player.plane.y, game->player.dir.x - game->player.plane.x, &ray_left);  // ray for leftmost
	fill_coord(game->player.dir.y + game->player.plane.y, game->player.dir.x + game->player.plane.x, &ray_right); // ray for rightmos
	int half_height;

	half_height = HEIGHT / 2;
	posZ = half_height; // center_camera 540
	double interpolate_y;
	double interpolate_x;
	interpolate_y = (ray_right.y - ray_left.y) / WIDTH;
	interpolate_x = (ray_right.x - ray_left.x) / WIDTH;
	while (++y < HEIGHT)
	{
		p = y - half_height; // distance from camera to y (-540 540)
		rowDist = posZ / (double)p;
		fill_coord(rowDist * interpolate_y, rowDist * interpolate_x, &floorStep); // get step
		fill_coord(game->player.pos.y + rowDist * ray_left.y, game->player.pos.x + rowDist * ray_left.x, &floor);

		x = -1;
		double min;
		min = 0;
		while (++x < WIDTH)
		{
			// cellX = (int)floor.x;
			// cellY = (int)floor.y;
			if (((int)floor.x + (int)floor.y) % 2 == 0)
			{
				floor_tex = 2;
				ceil_tex = 1;
			}
			else
			{
				floor_tex = 1;
				ceil_tex = 2;
			}
			tx = (int)(game->tex_img[floor_tex]->width * (floor.x - (int)floor.x)) & (game->tex_img[floor_tex]->width - 1);	  // get first x coord
			ty = (int)(game->tex_img[floor_tex]->height * (floor.y - (int)floor.y)) & (game->tex_img[floor_tex]->height - 1); // get first y coord
			color = game->texture[floor_tex][ty][tx];
			game->buffer[y][x] = color;
			tx = (int)(game->tex_img[ceil_tex]->width * (floor.x - (int)floor.x)) & (game->tex_img[ceil_tex]->width - 1);	// get first x coord
			ty = (int)(game->tex_img[ceil_tex]->height * (floor.y - (int)floor.y)) & (game->tex_img[ceil_tex]->height - 1); // get first y coord
			color = game->texture[ceil_tex][ty][tx];
			game->buffer[HEIGHT - y - 1][x] = color;
			fill_coord(floor.y + floorStep.y, floor.x + floorStep.x, &floor);
		}
	}
}
