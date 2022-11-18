/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <olugash@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 07:38:04 by olugash           #+#    #+#             */
/*   Updated: 2022/11/18 22:22:40 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	get_graphic(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		game_exit("Mlx init error\n");
	game->window = mlx_new_window(game->mlx, WIDTH, HEIGHT, "game");
	if (!game->window)
		game_exit("Mlx window error");
	game->img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img.img)
		game_exit("Image error");
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp,
			&game->img.line_length, &game->img.endian);
	if (!game->img.addr)
		game_exit("Image address error");
	mlx_mouse_hide();
	mlx_mouse_move(game->window, WIDTH / 2, HEIGHT / 2);
}

static void	init_buffer(t_game *game)
{
	int	y;

	y = -1;
	game->buffer = malloc(sizeof(int *) * (HEIGHT + 1));
	if (!game->buffer)
		game_exit("Malloc error\n");
	while (++y < HEIGHT)
	{
		game->buffer[y] = malloc(sizeof(int *) * (WIDTH + 1));
		game->buffer[y][WIDTH] = '\0';
		if (!game->buffer[y])
			game_exit("Malloc error\n");
	}
	game->buffer[HEIGHT] = NULL;
	game->zbuffer = malloc(sizeof(double) * WIDTH);
	if (!game->zbuffer)
		game_exit("Mallloc error\n");
}

t_game	*init_game(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
		game_exit("The number of arguments must be equal to two");
	game = malloc(sizeof(t_game));
	if (!game)
		game_exit("Malloc error\n");
	init_map(game, argv);
	get_graphic(game);
	init_textures(game);
	init_buffer(game);
	init_health_frame(game);
	init_minimap_frame(game);
	malloc_start(game);
	get_start(game);
	return (game);
}
