/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_perp_wall_dist.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <olugash@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 07:00:04 by olugash           #+#    #+#             */
/*   Updated: 2022/11/18 08:09:01 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	get_ray_dir(t_coord *ray_dir, int x, t_coord *delta_dist, t_game *game)
{
	double	camera_x;

	camera_x = (2 * x / (double)WIDTH - 1.0);
	fill_coord(game->player.dir.y + game->player.plane.y * camera_x,
		game->player.dir.x + game->player.plane.x * camera_x, ray_dir);
	delta_dist->x = fabs(1 / ray_dir->x);
	delta_dist->y = fabs(1 / ray_dir->y);
}

void	get_side_dist(t_ray *ray, t_game *game)
{
	fill_coord((int)game->player.pos.y, (int)game->player.pos.x, &ray->map);
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (game->player.pos.x - ray->map.x)
			* ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map.x + 1.0 - game->player.pos.x)
			* ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (game->player.pos.y - ray->map.y)
			* ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map.y + 1.0 - game->player.pos.y)
			* ray->delta_dist.y;
	}
}

static int	is_door(t_ray *ray, t_game *game)
{
	if (game->map->map_grid[(int)ray->map.y][(int)ray->map.x] == 'D'
			&& game->map->door_map[(int)ray->map.y][(int)ray->map.x].open
				== -1)
	{
		if (game->map
			->door_map[(int)ray->map.y][(int)ray->map.x].is_vertical == 0)
			ray->side = 2;
		else
			ray->side = 3;
		return (1);
	}
	return (0);
}

void	find_wall(t_ray *ray, t_game *game)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map.y += ray->step.y;
			ray->side = 1;
		}
		if (game->map->map_grid[(int)ray->map.y][(int)ray->map.x] == '1')
			hit = 1;
		else
			hit = is_door(ray, game);
	}
}

void	get_perp_wall_dist(t_wall_verline *verline, t_game *game)
{
	get_ray_dir(&verline->ray.dir, verline->x, &verline->ray.delta_dist, game);
	get_side_dist(&verline->ray, game);
	find_wall(&verline->ray, game);
	if (verline->ray.side == 0 || verline->ray.side == 2)
		verline->perpwalldist = verline->ray.side_dist.x
			- verline->ray.delta_dist.x;
	else
		verline->perpwalldist = verline->ray.side_dist.y
			- verline->ray.delta_dist.y;
}
