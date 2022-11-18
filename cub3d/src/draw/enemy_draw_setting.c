/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_draw_setting.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <olugash@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 06:59:06 by olugash           #+#    #+#             */
/*   Updated: 2022/11/18 06:59:40 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	select_action(t_game *game, int id, t_sprite_draw *draw_data, int i)
{
	game->enemy[id]->frame++;
	if (game->enemy[id]->frame == 1000)
		game->enemy[id]->frame = 0;
	if (game->enemy[id]->health <= 0)
		death_action(game, id);
	else if (game->sprite[i]->distance < 1)
		attack_action(game, id);
	else if (game->enemy[id]->action > game->enemy[id]->count_spawn)
		move_action(game, id, i);
	else if (game->sprite[i]->distance < 100.0)
		spawn_action(id, game);
	draw_data->start_tex_x = (game->tex_img[draw_data->tex_id]->width - 1.0)
		/ game->enemy[id]->count_actions * game->enemy[id]->action;
}

void	enemy_draw_setting(int i, t_sprite_draw *draw_data, t_game *game)
{
	int	id;

	id = game->sprite[i]->id - 8;
	if (id >= 0 && id <= 3)
	{
		draw_data->step_x /= game->enemy[id]->count_actions;
		select_action(game, id, draw_data, i);
	}
}
