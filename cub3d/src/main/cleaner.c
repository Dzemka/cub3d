#include <cub3d.h>

void clean_massive(void ***ptr)
{
	int i;
	char **ptr_ptr;

	i = -1;
	ptr_ptr = (char **)*ptr;
	if (ptr_ptr[0])
	{
		while (ptr_ptr[++i])
			free((*ptr)[i]);
	}
	free(ptr_ptr);
	ptr_ptr = NULL;
}

int cleaning_map(t_map **ptr)
{
	int row;
	t_map *map;

	map = *ptr;
	if (map->path_textures)
		clean_massive((void ***)&map->path_textures);
	if (map->map_grid)
		clean_massive((void ***)&map->map_grid);
	if (map->map_base)
		ft_lstclear(&map->map_base, free);
	free(map);
	map = NULL;
	return (1);
}

void clean_textures(int ****tex)
{
	int tex_id;
	int y;
	int ***tex_ptr;

	tex_ptr = *tex;
	tex_id = -1;

	if (tex_ptr[0])
	{
		while (++tex_id < 4)
		{

			if (tex_ptr[tex_id][0])
			{
				y = -1;
				while (tex_ptr[tex_id][++y])
					free(tex_ptr[tex_id][y]);
			}
			free(tex_ptr[tex_id]);
		}
	}
	free(tex_ptr);
}

void clean_tex_img(t_game *game)
{
	int i;

	i = -1;
	while (++i < 4)
		mlx_destroy_image(game->mlx, game->tex_img[i]->img);
}

void game_clean(t_game **game)
{
	// exit(1);
	if ((*game)->map)
		cleaning_map(&(*game)->map);
	//problem
	if ((*game)->buffer)
		clean_massive((void ***)&(*game)->buffer);
	//problem

	if (((*game)->texture))
		clean_textures(&(*game)->texture);
	if ((*game)->tex_img)
		clean_tex_img(*game);
	exit(1);
}
