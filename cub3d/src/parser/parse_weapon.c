#include <cub3d.h>

int parse_weapon(char *s, int i, t_map *map)
{
	if (s[i] == 'W')
	{
		i++;
		if (s[i] == '\0')
			game_exit("Weapon texture not found");
		if (map->path_weapon)
			game_exit("Weapon texture declared more than once");
		if (s[i] != ' ' && s[i + 1] != '\t')
			game_exit("No separator after weapon id");
		while (s[i] == ' ' || s[i] == '\t')
			i++;
		if (s[i] == '\0')
			game_exit("Weapon texture not found");
		map->path_weapon = ft_strdup(&s[i]);
		if (!map->path_weapon)
			game_exit("Malloc error\n");
		return (1);
	}
	else
		return (0);
}
