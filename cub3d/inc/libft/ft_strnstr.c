/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 20:44:02 by olugash           #+#    #+#             */
/*   Updated: 2021/10/12 20:44:24 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strnstr(const	char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	len_needle;

	i = 0;
	len_needle = ft_strlen(needle);
	if (needle[0] == '\0')
		return ((char *)haystack);
	if (ft_strlen(haystack) < len_needle)
		return (NULL);
	while (i < len && haystack[i] != '\0')
	{
		if (ft_strchr(needle, haystack[i]) && i + len_needle <= len)
		{
			if (ft_memcmp(needle, (char *)haystack + i, len_needle) == 0)
			{
				return ((char *)haystack + i);
			}
		}
		i++;
	}
	return (NULL);
}
