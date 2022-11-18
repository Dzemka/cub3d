/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <olugash@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 07:28:40 by olugash           #+#    #+#             */
/*   Updated: 2022/11/18 07:58:42 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	get_enemy(t_game *game)
{
	int	i;

	i = -1;
	while (++i < ENEMY_COUNT)
		*game->enemy[i] = *game->map->enemy_base[i];
}

static void	get_start_values(t_game *game)
{
	fill_coord(game->map->player_p.y + 0.5,
		game->map->player_p.x + 0.5, &game->player.pos);
	game->map
		->map_grid[(int)game->map->player_p.y][(int)game->map->player_p.x]
		= '0';
	game->player.health = 100;
	game->player.frame = 0;
	game->player.weapon_action = 0;
	game->player.attack = 0;
	game->player.action = 0;
	game->pitch = 0;
}

static void	get_player(t_game *game)
{
	if (game->map->player_orientation == 'N')
	{
		fill_coord(-1, 0, &game->player.dir);
		fill_coord(0, FOV, &game->player.plane);
	}
	else if (game->map->player_orientation == 'W')
	{
		fill_coord(0, -1, &game->player.dir);
		fill_coord(-FOV, 0, &game->player.plane);
	}
	else if (game->map->player_orientation == 'S')
	{
		fill_coord(1, 0, &game->player.dir);
		fill_coord(0, -FOV, &game->player.plane);
	}
	else if (game->map->player_orientation == 'E')
	{
		fill_coord(0, 1, &game->player.dir);
		fill_coord(FOV, 0, &game->player.plane);
	}
	get_start_values(game);
}

static void	get_sprites(t_map *map)
{
	size_t	x;
	size_t	y;

	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (map->map_grid[y][++x])
		{
			if (ft_strchr("6789", map->map_grid[y][x]))
				map->map_grid[y][x] = '0';
			if (map->map_grid[y][x] == 'D')
			{
				if (map->map_grid[y][x + 1] == '1'
					&& map->map_grid[y][x - 1] == '1')
					map->door_map[y][x].is_vertical = 1;
				else if (map->map_grid[y + 1][x] == '1'
					&& map->map_grid[y - 1][x] == '1')
					map->door_map[y][x].is_vertical = 0;
				else
					game_exit("Door must be between two walls");
				map->door_map[y][x].open = -1;
			}
		}
	}
}

void	get_start(t_game *game)
{
	int	i;

	get_sprites(game->map);
	i = -1;
	while (++i < game->map->sprite_count)
		*game->sprite[i] = *game->map->sprite_base[i];
	get_enemy(game);
	get_player(game);
	game->funct = &draw_game;
}
