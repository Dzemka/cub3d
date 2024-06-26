/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <olugash@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 07:46:40 by olugash           #+#    #+#             */
/*   Updated: 2022/11/18 07:46:41 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	main(int argc, char **argv)
{
	t_game	*game;

	game = init_game(argc, argv);
	hooks(game);
	mlx_loop(game->mlx);
	return (0);
}
