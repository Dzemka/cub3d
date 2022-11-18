/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <olugash@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 08:00:04 by olugash           #+#    #+#             */
/*   Updated: 2022/11/18 08:02:03 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	get_object(int x, int y, t_map *map, int *sprite_index)
{
	char	tex_id;

	tex_id = map->map_grid[y][x] - 48 + 4 - 2;
	(*sprite_index)++;
	map->sprite_base[*sprite_index]->id = tex_id;
	map->sprite_base[*sprite_index]->main_id = *sprite_index;
	fill_coord(y + 0.5, x + 0.5, &map->sprite_base[*sprite_index]->coord);
}

static void	init_tile(int x, int y, t_map *map, int *sprite_index)
{
	char	c;

	c = map->map_grid[y][x];
	if (ft_strchr("NSWE", c))
	{
		if (map->player_orientation != '\0')
			game_exit("Player must be only one");
		map->player_orientation = c;
		fill_coord(y, x, &map->player_p);
	}
	if (ft_strchr("23456789", c))
		get_object(x, y, map, sprite_index);
}

static int	check_around(t_map *map, size_t y, size_t x)
{
	size_t	len;

	len = ft_strlen(map->map_grid[y]);
	return (y == 0
		|| y == map->height - 1
		|| x == 0
		|| x == len - 1
		|| x >= ft_strlen(map->map_grid[y + 1])
		|| x >= ft_strlen(map->map_grid[y - 1])
		|| map->map_grid[y][x - 1] == ' '
		|| map->map_grid[y][x + 1] == ' '
		|| map->map_grid[y - 1][x] == ' '
		|| map->map_grid[y + 1][x] == ' ');
}

static void	check_tile(int x, int y, t_map *map)
{
	char	c;

	c = map->map_grid[y][x];
	if (!ft_strchr("0123456789NSEWD ", c))
	{
		printf("Line %d, Column %d : \"%c\" - undefined symbol\n",
			y, x + 1, c);
		exit(1);
	}
	if (ft_strchr("023456789NSWED", c))
	{
		if (check_around(map, y, x))
			game_exit("The walls are not closed");
	}
}

void	parse_tile(int x, int y, t_map *map, int *sprite_index)
{
	check_tile(x, y, map);
	init_tile(x, y, map, sprite_index);
}
