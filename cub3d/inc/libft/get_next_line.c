/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <olugash@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 01:48:51 by olugash           #+#    #+#             */
/*   Updated: 2022/09/27 12:56:17 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list_gnl	*ft_clr_elem(t_list_gnl *list, t_list_gnl *elem)
{
	t_list_gnl	*temp;

	if (list == elem)
	{
		list = list->next;
		free(elem);
	}
	else
	{
		temp = list;
		while (temp->next != elem)
			temp = temp->next;
		temp->next = elem->next;
		free(elem);
	}
	return (list);
}

t_list_gnl	*ft_select_elem(t_list_gnl *list, int fd)
{
	t_list_gnl	*elem;

	if (!list)
		return (NULL);
	elem = list;
	while (elem->fd != fd)
	{
		if (elem->fd != fd && !elem->next)
			elem->next = ft_lst_new(fd);
		elem = elem->next;
	}
	return (elem);
}

static char	*ft_get_remaining(t_gnl *gnl, char *remaining_str)
{
	char	*temp_reamaining;

	temp_reamaining = NULL;
	if (!remaining_str)
		return (NULL);
	gnl->end_line = ft_strchr(remaining_str, '\n');
	if (gnl->end_line)
		if (*(++gnl->end_line) != '\0')
			temp_reamaining = ft_strdup(gnl->end_line);
	gnl->new_line = ft_build_line(gnl->new_line, remaining_str, gnl->end_line);
	free (remaining_str);
	return (temp_reamaining);
}

static char	*ft_get_res(int fd, char *buf, t_gnl *gnl, t_list_gnl *elem)
{
	ssize_t	count_read;

	gnl->new_line = NULL;
	gnl->end_line = NULL;
	elem->remaining_str = ft_get_remaining(gnl, elem->remaining_str);
	while (!gnl->end_line)
	{
		count_read = read(fd, buf, BUFFER_SIZE);
		if (count_read == 0)
			break ;
		if (count_read == -1)
		{
			if (gnl->new_line)
				free (gnl->new_line);
			return (NULL);
		}
		buf[count_read] = '\0';
		gnl->end_line = ft_strchr(buf, '\n');
		if (gnl->end_line)
			if (*(++gnl->end_line) != '\0')
				elem->remaining_str = ft_strdup(gnl->end_line);
		gnl->new_line = ft_build_line(gnl->new_line, buf, gnl->end_line);
	}
	return (gnl->new_line);
}

char	*get_next_line(int fd)
{
	t_gnl				*gnl;
	char				*buf;
	char				*res;
	static t_list_gnl	*list;
	t_list_gnl			*elem;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	res = NULL;
	if (!list)
		list = ft_lst_new(fd);
	elem = ft_select_elem(list, fd);
	buf = malloc(BUFFER_SIZE + 1);
	gnl = (t_gnl *)malloc(sizeof(t_gnl));
	if (buf && gnl && elem)
		res = ft_get_res(fd, buf, gnl, elem);
	if (gnl)
		free (gnl);
	if (buf)
		free (buf);
	if (elem)
		if (elem->remaining_str == NULL)
			list = ft_clr_elem(list, elem);
	return (res);
}
