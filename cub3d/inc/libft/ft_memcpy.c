/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 18:52:26 by olugash           #+#    #+#             */
/*   Updated: 2021/10/14 18:52:27 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	size_t	i;
	char	*dst_ch;
	char	*src_ch;

	if (dst == NULL && src == NULL)
		return (NULL);
	i = 0;
	dst_ch = (char *)dst;
	src_ch = (char *)src;
	while (i < n)
	{
		dst_ch[i] = src_ch[i];
		i++;
	}
	return (dst_ch);
}
