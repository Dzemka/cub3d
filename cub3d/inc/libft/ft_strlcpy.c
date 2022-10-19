/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 18:00:21 by olugash           #+#    #+#             */
/*   Updated: 2021/10/09 18:00:23 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *restrict dst, const char *restrict src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = dstsize - 1;
	j = 0;
	if (dstsize != 0)
	{
		while (i > 0 && src[j] != '\0')
		{
			dst[j] = src[j];
			j++;
			i--;
		}
		dst[j] = '\0';
	}
	return (ft_strlen(src));
}
