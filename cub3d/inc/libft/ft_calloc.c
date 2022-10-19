/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 23:10:22 by olugash           #+#    #+#             */
/*   Updated: 2021/10/14 23:10:24 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*str;

	str = NULL;
	str = malloc(count * size);
	if (str == NULL)
		return (NULL);
	ft_memset (str, 0, size * count);
	return (str);
}
