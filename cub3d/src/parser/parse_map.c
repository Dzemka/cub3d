/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <olugash@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 07:53:11 by olugash           #+#    #+#             */
/*   Updated: 2022/11/18 22:40:05 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	parse_id(char *s, int i, t_map *map, t_list *tmp)
{
	if (parse_textures(s, i, map))
		return ;
	if (parse_color(s, i, map))
		return ;
	if (parse_enemy(s, i, map))
		return ;
	if (s[i] == '1')
		map->grid_ptr = tmp;
	else
	{
		printf("%s", s);
		game_exit(": undefined id");
	}
}

static void	parse_line(char *s, t_map *map, t_list *tmp)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	if (s[len - 1] == '\n')
		s[len - 1] = '\0';
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	if (s[i] == '\0')
		return ;
	if (!map->grid_ptr)
		parse_id(s, i, map, tmp);
	else if (len > map->width)
		map->width = len;
}

static void	read_line(t_map *map, int fd, int *read_end)
{
	t_list	*ptr;
	char	*line;

	line = get_next_line(fd);
	if (!line)
	{
		*read_end = 1;
		return ;
	}
	ptr = ft_lstnew(line);
	if (!ptr)
		game_exit("Malloc error\n");
	ft_lstadd_back(&map->linelist, ptr);
	parse_line(line, map, ptr);
}

void	parse_map(t_game *game, int fd)
{
	int	read_end;

	read_end = 0;
	while (!read_end)
		read_line(game->map, fd, &read_end);
	parse_grid(game);
	check_map_fill(game);
}
