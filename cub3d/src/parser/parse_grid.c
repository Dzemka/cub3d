/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_grid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <olugash@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 07:52:04 by olugash           #+#    #+#             */
/*   Updated: 2022/11/18 07:53:01 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	scan_grid(t_map *map)
{
	size_t	x;
	size_t	y;
	int		sprite_index;

	y = -1;
	sprite_index = -1;
	while (++y < map->height)
	{
		x = -1;
		while (map->map_grid[y][++x])
			parse_tile(x, y, map, &sprite_index);
		x--;
		while (++x < map->width)
			map->map_grid[y][x] = '-';
	}
}

static void	malloc_sprites(t_game *game)
{
	int	i;

	game->map->sprite_base = malloc(sizeof(t_sprite *)
			* (game->map->sprite_count + 1));
	if (!game->map->sprite_base)
		game_exit("Malloc error\n");
	game->map->sprite_base[game->map->sprite_count] = NULL;
	i = -1;
	while (++i < game->map->sprite_count)
	{
		game->map->sprite_base[i] = malloc(sizeof(t_sprite));
		if (!game->map->sprite_base[i])
			game_exit("Malloc error\n");
	}
}

static void	malloc_door_map(t_game *game)
{
	size_t	i;
	size_t	j;

	game->map->door_map = malloc(sizeof(t_door_map *)
			* (game->map->height + 1));
	if (!game->map->door_map)
		game_exit("Malloc error\n");
	game->map->door_map[game->map->height] = NULL;
	i = -1;
	while (++i < game->map->height)
	{
		game->map->door_map[i]
			= malloc(sizeof(t_door_map) * (game->map->width + 1));
		if (!game->map->door_map[i])
			game_exit("Malloc error\n");
		j = -1;
		while (++j < game->map->width)
			game->map->door_map[i][j].open = 0;
	}
}

void	parse_grid(t_game *game)
{
	copy_grid(game->map);
	malloc_sprites(game);
	malloc_door_map(game);
	scan_grid(game->map);
}
