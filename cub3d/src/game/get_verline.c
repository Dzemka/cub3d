#include <cub3d.h>

void get_ray_dir(t_coord *rayDir, int x, t_game *game)
{
	double cameraX;

	cameraX = (2 * x / (double)WIDTH - 1.0);
	fill_coord(game->player->dir->y + game->player->plane->y * cameraX,
			   game->player->dir->x + game->player->plane->x * cameraX, rayDir);
}

void get_delta_dist(t_coord *deltaDist, t_coord rayDir)
{
	deltaDist->x = fabs(1 / rayDir.x);
	deltaDist->y = fabs(1 / rayDir.y);
}

void get_side_dist(t_ray *ray, t_game *game)
{
	fill_coord((int)game->player->pos->y, (int)game->player->pos->x, &ray->map);
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->sideDist.x = (game->player->pos->x - ray->map.x) * ray->deltaDist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->sideDist.x = (ray->map.x + 1.0 - game->player->pos->x) * ray->deltaDist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->sideDist.y = (game->player->pos->y - ray->map.y) * ray->deltaDist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->sideDist.y = (ray->map.y + 1.0 - game->player->pos->y) * ray->deltaDist.y;
	}
}

void find_wall(t_ray *ray, char **map)
{
	int hit;
	int count;

	count = 0;
	hit = 0;
	while (hit == 0)
	{
		if (ray->sideDist.x < ray->sideDist.y)
		{
			ray->sideDist.x += ray->deltaDist.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->sideDist.y += ray->deltaDist.y;
			ray->map.y += ray->step.y;
			ray->side = 1;
		}
		if (map[(int)ray->map.y][(int)ray->map.x] == '1')
			hit = 1;
		count++;
	}
}

void get_verline(int x, t_game *game, int *drawStart, int *drawEnd)
{
	t_ray ray;
	double perpWallDist;
	int line_height;

	get_ray_dir(&ray.dir, x, game);
	get_delta_dist(&ray.deltaDist, ray.dir);
	get_side_dist(&ray, game);
	find_wall(&ray, game->map->map_grid);
	if (ray.side == 0)
		perpWallDist = ray.sideDist.x - ray.deltaDist.x;
	else
		perpWallDist = ray.sideDist.y - ray.deltaDist.y;
	line_height = (int)(HEIGHT / perpWallDist);

	double texY;
	double step;

	step = (double)TEX_HEIGHT / (double)line_height;
	texY = 0;
	*drawStart = HEIGHT / 2 - line_height / 2 + game->pitch;
	if (*drawStart < 0)
	{
		texY = *drawStart * step * -1;
			*drawStart = 0;
	}
	*drawEnd = HEIGHT / 2 + line_height / 2 + game->pitch;
	if (*drawEnd >= HEIGHT)
		*drawEnd = HEIGHT - 1;

	// test
	double wallX;
	int texNum = 0;
	if (ray.side == 0)
		wallX = game->player->pos->y + perpWallDist * ray.dir.y;
	else
		wallX = game->player->pos->x + perpWallDist * ray.dir.x;
	if (ray.side == 0)
	{
		if (ray.dir.x < 0)
			texNum = 2;
		else
			texNum = 3;
	}
	else
	{
		if (ray.dir.y < 0)
			texNum = 0;
		else
			texNum = 1;
	}
	wallX -= floor(wallX);
	int texX;

	texX = (int)(wallX * (double)(TEX_WIDTH));
	// double step = 1.0 * TEX_HEIGHT / line_height;
	// double tex_pos = (*drawStart - HEIGHT / 2 + line_height / 2 - game->pitch) * step;
	// double tex_pos = 0;
	// if (*drawStart < 0)
	// {
	// 	tex_pos = ((line_height - HEIGHT) / 2) * step;
	// 	*drawStart = 0;
	// }
	// double texY;

	// texY = 0;
	// if (*drawStart < 0)
	// {
	// 	texY = *drawStart * step * -1;
	// 	*drawStart = 0;
	// }
	int t;
	t = *drawStart - 1;
	while (++t < *drawEnd)
	{
		// printf("%d\n", t);
		// int texY = (int)tex_pos & (int)(TEX_HEIGHT - 1);
		// if (*drawEnd > HEIGHT - 1)
		// 	break;
		if (texY >= 0 && texY < TEX_HEIGHT - 1)
			game->buffer[t][x] = game->texture[texNum][(int)texY][texX]; //сделать чтобы использовались текстуры разных разрешений
																		 // if (ray.side == 0)
																		 // game->wall_color = (game->wall_color >> 1) & 8355711;
		texY += step;
		// texY++;
	}
	game->zBuffer[x] = perpWallDist;
	// test
}
