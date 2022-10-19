/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 14:32:39 by olugash           #+#    #+#             */
/*   Updated: 2021/10/16 14:32:41 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	max_len;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (len == 0 || start >= ft_strlen(s))
		return (ft_calloc(1, sizeof(char)));
	max_len = ft_strlen(s);
	if (max_len > len)
		max_len = len;
	str = (char *)malloc(sizeof(char) * (max_len + 1));
	if (!str)
		return (NULL);
	while (i < max_len)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}
