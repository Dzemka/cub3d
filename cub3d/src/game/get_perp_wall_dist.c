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

void	get_perp_wall_dist(t_wall_verline *verline, t_game *game)
{
	get_ray_dir(&verline->ray.dir, verline->x, game);
	get_delta_dist(&verline->ray.deltaDist, verline->ray.dir);
	get_side_dist(&verline->ray, game);
	find_wall(&verline->ray, game->map->map_grid);
	if (verline->ray.side == 0)
		verline->perpWallDist = verline->ray.sideDist.x - verline->ray.deltaDist.x;
	else
		verline->perpWallDist = verline->ray.sideDist.y - verline->ray.deltaDist.y;
}
