/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <olugash@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 01:52:59 by olugash           #+#    #+#             */
/*   Updated: 2022/09/27 13:11:29 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_build_line(char *str1, char *str2, char *end_line)
{
	char	*new_str;
	size_t	len_new_str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!str2)
		return (NULL);
	if (!str1)
		str1 = ft_strdup("");
	len_new_str = ft_strlen(str1) + ft_strlen(str2) + 1;
	new_str = malloc(len_new_str);
	if (!new_str)
		return (NULL);
	if (end_line)
		*(end_line) = '\0';
	while (str1[j] != '\0')
		new_str[i++] = str1[j++];
	j = 0;
	while (str2[j] != '\0')
		new_str[i++] = str2[j++];
	new_str[i] = '\0';
	free (str1);
	return (new_str);
}

t_list_gnl	*ft_lst_new(int fd)
{
	t_list_gnl	*lst_new;

	lst_new = (t_list_gnl *)malloc(sizeof(t_list_gnl));
	if (!lst_new)
		return (NULL);
	lst_new->fd = fd;
	lst_new->remaining_str = NULL;
	lst_new->next = NULL;
	return (lst_new);
}
