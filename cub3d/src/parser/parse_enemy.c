/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_enemy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <olugash@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 07:51:33 by olugash           #+#    #+#             */
/*   Updated: 2022/11/18 07:51:48 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

char	**get_fields(char *s, int i)
{
	char	**data;
	int		j;

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
			if (!ft_isdigit(data[i][j]))
				game_exit("fields consist only the numbers");
	}
	if (i != 6)
		game_exit("Enemy  must have 6 fields");
	return (data);
}

int	parse_enemy(char *s, int i, t_map *map)
{
	char	**data;
	int		enemy_id;

	if (s[i] == 'E')
	{
		data = get_fields(s, i);
		enemy_id = s[i + 1] - 48;
		if (map->enemy_base[enemy_id]->sprite_index != -1)
			game_exit("Enemy declared more than once");
		map->enemy_base[enemy_id]->sprite_index = ft_atoi(data[0]);
		map->enemy_base[enemy_id]->count_actions = ft_atoi(data[1]);
		map->enemy_base[enemy_id]->count_spawn = ft_atoi(data[2]);
		map->enemy_base[enemy_id]->count_walk = ft_atoi(data[3]);
		map->enemy_base[enemy_id]->count_attack = ft_atoi(data[4]);
		map->enemy_base[enemy_id]->count_dead = ft_atoi(data[5]);
		map->enemy_base[enemy_id]->frame = 0;
		map->enemy_base[enemy_id]->action = 0;
		map->enemy_base[enemy_id]->health = 100;
		i = -1;
		while (data[++i])
			free(data[i]);
		free(data);
		return (1);
	}
	return (0);
}
