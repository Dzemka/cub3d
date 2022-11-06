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
	ray->test += count;
}

void get_verline(int x, t_game *game, int *drawStart, int *drawEnd)
{
	t_ray ray;
	double perpWallDist;
	int line_height;

	ray.test = 0;
	get_ray_dir(&ray.dir, x, game);
	get_delta_dist(&ray.deltaDist, ray.dir);
	fill_coord((int)game->player->pos->y, (int)game->player->pos->x, &ray.map);
	get_side_dist(&ray, game);
	find_wall(&ray, game->map->map_grid);
	if (ray.side == 0)
		perpWallDist = ray.sideDist.x - ray.deltaDist.x;
	else
		perpWallDist = ray.sideDist.y - ray.deltaDist.y;
	line_height = (int)(HEIGHT / perpWallDist);
	*drawStart = HEIGHT / 2 - line_height / 2 + game->pitch + (game->posZ / perpWallDist);
	if (*drawStart < 0)
		*drawStart = 0;
	*drawEnd = HEIGHT / 2 + line_height / 2 + game->pitch + (game->posZ / perpWallDist);
	if (*drawEnd >= HEIGHT)
		*drawEnd = HEIGHT - 1;

	// test
	double wallX;
	int texNum = 0; // number wall id - char to int
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
	if (ray.side == 0 & ray.dir.x > 0)
		texX = TEX_WIDTH - texX - 1;
	if (ray.side == 1 & ray.dir.y < 0)
		texX = TEX_WIDTH - texX - 1;
	double step = 1.0 * TEX_HEIGHT / line_height;
	double tex_pos = (*drawStart - game->pitch - (game->posZ / perpWallDist) - HEIGHT / 2 + line_height / 2) * step;
	int t;
	t = *drawStart - 1;
	while (++t < *drawEnd)
	{
		int texY = (int)tex_pos & (int)(TEX_HEIGHT - 1);
		tex_pos += step;
		game->buffer[t][x] = game->texture[texNum][texY][texX]; //сделать чтобы использовались текстуры разных разрешений
																// if (ray.side == 0)
																// game->wall_color = (game->wall_color >> 1) & 8355711;
	}
	game->zBuffer[x] = perpWallDist;
	// test
}
