/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 17:40:55 by olugash           #+#    #+#             */
/*   Updated: 2021/10/09 17:40:57 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*p;
	int		len;

	p = (char *)s;
	len = ft_strlen(p);
	while (len >= 0)
	{
		if (p[len] == (char)c)
			return (p + len);
		len--;
	}
	return (NULL);
}
