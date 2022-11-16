#include <cub3d.h>

static int select_color(t_game *game, int map_x, int map_y)
{
	if (map_y >= 0 && map_y < game->map->height && map_x >= 0 && map_x < game->map->width)
	{
		if (game->map->map_grid[(int)map_y][(int)map_x] == '-' || game->map->map_grid[(int)map_y][(int)map_x] == ' ')
			return (0x1);
		else if (game->map->map_grid[(int)map_y][(int)map_x] == '1')
			return (0x480607);
		else if (game->map->map_grid[(int)map_y][(int)map_x] == '0')
			return (0x4E5754);
		else if (ft_strchr("6789", game->map->map_grid[(int)map_y][(int)map_x]))
			return (0xFF0000);
		else if (ft_strchr("2345", game->map->map_grid[(int)map_y][(int)map_x]))
			return (0x00FF00);
	}
	else
		return(0x1);
}

void draw_minimap(t_game *game)
{
	int x;
	int y;
	double step;
	double map_x;
	double map_y;
	double start;

	map_x = (double)game->player.pos.x - RANGE_MINIMAP / 2.0;
	map_y = (double)game->player.pos.y - RANGE_MINIMAP / 2.0;
	start = map_x;
	step = (double)RANGE_MINIMAP / (double)game->minimap_size;
	y = -1;
	while (game->minimap_frame_buffer[++y])
	{
		x = -1;
		map_x = start;
		while (game->minimap_frame_buffer[y][++x])
		{
			if (game->minimap_frame_buffer[y][x] != 16777216)
			{
				if (game->minimap_frame_buffer[y][x] == 0x1)
					game->buffer[y][x] = select_color(game, map_x, map_y);
				else
					game->buffer[y][x] = game->minimap_frame_buffer[y][x];
			}
			map_x += step;
		}
		map_y += step;
	}
}
