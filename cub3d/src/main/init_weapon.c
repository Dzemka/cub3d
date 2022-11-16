#include <cub3d.h>

static void set_color(char *addr, int *color)
{
	*color = addr[0];
	*color += addr[1] * 256;
	*color += addr[2] * 256 * 256;
	*color += 256 * 256 * 256;
}

void	get_texture(t_game *game)
{
	int	y;
	int	x;

	y = -1;
	while (++y < game->weapon_img.height)
	{
		x = -1;
		while (++x < game->weapon_img.width)
			set_color(&game->weapon_img.addr[y * game->weapon_img.line_length + x * 4], &game->weapon_tex[y][x]);
	}
}

void init_weapon(t_game *game)
{
	int y;

	game->weapon_img.img = mlx_xpm_file_to_image(game->mlx, game->map->path_weapon, &game->weapon_img.width, &game->weapon_img.height);
	if (!game->weapon_img.img)
		game_exit("Weapon img error");
	game->weapon_img.addr = mlx_get_data_addr(game->weapon_img.img, &game->weapon_img.bpp, &game->weapon_img.line_length, &game->weapon_img.endian);
	if (!game->weapon_img.addr)
		game_exit("Weapon addr error");
	game->weapon_tex = malloc(sizeof(int *) * (game->weapon_img.height + 1));
	if (!game->weapon_tex)
		game_exit("Malloc error\n");
	game->weapon_tex[game->weapon_img.height] = NULL;
	y = -1;
	while (++y < game->weapon_img.height)
	{
		game->weapon_tex[y] = malloc(sizeof(int) * game->weapon_img.width);
		if (!game->weapon_tex[y])
			game_exit("Malloc error");
		game->weapon_tex[y][game->weapon_img.width] = '\0';
	}
	get_texture(game);
}
