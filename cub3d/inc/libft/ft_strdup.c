/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 23:24:30 by olugash           #+#    #+#             */
/*   Updated: 2021/10/14 23:24:32 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*str_dup;

	i = 0;
	str_dup = NULL;
	while (s1[i])
		i++;
	str_dup = (char *)(malloc(sizeof(char) * i + 1));
	if (str_dup == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str_dup[i] = s1[i];
		i++;
	}
	str_dup[i] = '\0';
	return (str_dup);
}
