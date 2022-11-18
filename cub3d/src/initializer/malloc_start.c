/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <olugash@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 07:45:57 by olugash           #+#    #+#             */
/*   Updated: 2022/11/18 08:46:22 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	malloc_sprites(t_game *game)
{
	int	i;

	game->sprite = malloc(sizeof(t_sprite *) * (game->map->sprite_count + 1));
	if (!game->sprite)
		game_exit("Malloc error\n");
	i = -1;
	while (++i < game->map->sprite_count)
		game->sprite[i] = malloc(sizeof(t_sprite));
	game->sprite[game->map->sprite_count] = NULL;
}

static void	malloc_enemy(t_game *game)
{
	int	i;

	game->enemy = malloc(sizeof(t_sprite *) * (ENEMY_COUNT + 1));
	if (!game->enemy)
		game_exit("Malloc error\n");
	i = -1;
	game->enemy[ENEMY_COUNT] = NULL;
	while (++i < ENEMY_COUNT)
		game->enemy[i] = malloc(sizeof(t_enemy));
}

void	malloc_start(t_game *game)
{
	malloc_sprites(game);
	malloc_enemy(game);
}
