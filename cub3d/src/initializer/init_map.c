/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <olugash@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 07:41:00 by olugash           #+#    #+#             */
/*   Updated: 2022/11/18 22:29:34 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	init_map_values(t_map *map)
{
	int	i;

	i = -1;
	while (++i <= TEX_COUNT)
		map->path_textures[i] = NULL;
	map->floor_color = -1;
	map->ceiling_color = -1;
	map->linelist = NULL;
	map->grid_ptr = NULL;
	map->height = 0;
	map->width = 0;
	map->player_orientation = '\0';
	map->sprite_count = 0;
	map->enemy_count = 0;
	map->door_count = 0;
}

static void	get_map_base(t_game *game)
{
	int	i;

	game->map = malloc(sizeof(t_map));
	if (!game->map)
		game_exit("Malloc error\n");
	game->map->game = game;
	game->map->path_textures = malloc(sizeof(char *) * (TEX_COUNT + 1));
	if (!game->map->path_textures)
		game_exit("Malloc error\n");
	game->map->enemy_base = malloc(sizeof(t_enemy *) * (ENEMY_COUNT + 1));
	if (!game->map->enemy_base)
		game_exit("Malloc error\n");
	i = -1;
	game->map->enemy_base[ENEMY_COUNT] = NULL;
	while (++i < ENEMY_COUNT)
	{
		game->map->enemy_base[i] = malloc(sizeof(t_enemy));
		if (!game->map->enemy_base[i])
			game_exit("Malloc error\n");
		game->map->enemy_base[i]->sprite_index = -1;
	}
	init_map_values(game->map);
}

static int	get_fd(char *s)
{
	int	fd;

	fd = open(s, O_RDONLY);
	if (fd == -1)
	{
		perror(s);
		exit(errno);
	}
	return (fd);
}

void	init_map(t_game *game, char **argv)
{
	int	map_fd;

	map_fd = get_fd(argv[1]);
	get_map_base(game);
	parse_map(game, map_fd);
	ft_lstclear(&game->map->linelist, free);
	close(map_fd);
}
