/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 20:56:38 by olugash           #+#    #+#             */
/*   Updated: 2021/10/12 20:58:57 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void*s2, size_t	n)
{
	unsigned char		*str1;
	unsigned char		*str2;
	size_t				i;

	if (n == 0)
		return (0);
	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (i < n - 1 && str1[i] == str2[i])
	{
		i++;
	}
	return (str1[i] - str2[i]);
}
