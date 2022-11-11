#include <cub3d.h>

char **get_fields(char *s, int i, t_map *map)
{
	char **data;
	int j;

	if (s[i + 1] == '\0')
		game_exit("Enemy has no identificator");
	if (s[i + 1] < '0' && s[i + 1] > '3')
		game_exit("Index enemy in the range 0-3");
	if (s[i + 2] == '\0')
		game_exit("Enemy has no fields");
	data = ft_split(&s[i + 2], ':');
	if (!data)
		game_exit("malloc error\n");
	i = -1;
	while (data[++i])
	{
		j = -1;
		while (data[i][++j])
		{
			if (!ft_isdigit(data[i][j]))
				game_exit("fields consist only the numbers");
		}
	}
	if (i != 6)
		game_exit("Enemy  must have 6 fields");
	return (data);
}

int parse_enemy(char *s, int i, t_map *map)
{
	char **data;
	int enemy_id;
	t_game *game;

	game = map->game;
	if (s[i] == 'E')
	{
		data = get_fields(s, i, map);
		enemy_id = s[i + 1] - 48;
		game->enemy[enemy_id] = malloc(sizeof(t_enemy));
		game->enemy[enemy_id]->sprite_index = ft_atoi(data[0]);
		game->enemy[enemy_id]->count_actions = ft_atoi(data[1]);
		game->enemy[enemy_id]->count_spawn = ft_atoi(data[2]);
		game->enemy[enemy_id]->count_walk = ft_atoi(data[3]);
		game->enemy[enemy_id]->count_attack = ft_atoi(data[4]);
		game->enemy[enemy_id]->count_dead = ft_atoi(data[5]);
		game->enemy[enemy_id]->frame = 0;
		game->enemy[enemy_id]->action = 0;
		return (1);
	}
	return (0);
}
