/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <olugash@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 07:23:24 by olugash           #+#    #+#             */
/*   Updated: 2022/11/18 07:23:28 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	hooks(t_game *game)
{
	mlx_hook(game->window, 4, 1L << 2, &mouse_press, game);
	mlx_hook(game->window, 6, 1L << 6, &mouse_move, game);
	mlx_hook(game->window, 2, 1L << 0, &key_hooks, game);
	mlx_loop_hook(game->mlx, &game_start, game);
}
