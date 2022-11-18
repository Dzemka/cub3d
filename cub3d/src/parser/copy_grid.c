/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <olugash@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 07:50:37 by olugash           #+#    #+#             */
/*   Updated: 2022/11/18 07:50:43 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	get_obj_count(char *s, t_map *map)
{
	int	x;

	x = -1;
	while (s[++x])
	{
		if (ft_strchr("23456789", s[x]))
			map->sprite_count++;
		if (s[x] == 'D')
			map->door_count++;
	}
}

void	copy_grid(t_map *map)
{
	t_list	*line_ptr;
	size_t	y;

	map->height = ft_lstsize(map->grid_ptr);
	map->map_grid = malloc(sizeof(char *) * (map->height + 1));
	if (!map->map_grid)
		game_exit("Malloc error\n");
	line_ptr = map->grid_ptr;
	y = -1;
	while (++y < map->height)
	{
		map->map_grid[y] = malloc(sizeof(char) * map->width);
		if (!map->map_grid[y])
			game_exit("Malloc error");
		ft_strlcpy(map->map_grid[y], line_ptr->content, map->width);
		if (ft_strchr(map->map_grid[y], '\t'))
			game_exit("Map grid can not contain a tab");
		get_obj_count(map->map_grid[y], map);
		line_ptr = line_ptr->next;
	}
	map->map_grid[y] = NULL;
}
