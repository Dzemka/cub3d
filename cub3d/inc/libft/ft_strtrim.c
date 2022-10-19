/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:40:28 by olugash           #+#    #+#             */
/*   Updated: 2021/10/19 16:40:31 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	start;
	size_t	end;
	size_t	len;

	if (s1 == NULL || set == NULL)
		return (NULL);
	i = 0;
	start = 0;
	end = ft_strlen(s1);
	while (ft_strchr(set, s1[i]) != NULL && s1[i])
		i++;
	start = i;
	while (ft_strchr(set, s1[end - 1]) != NULL && start != end)
		end--;
	i = 0;
	len = end - start;
	str = malloc((sizeof(char) * (len + 1)));
	if (str == NULL)
		return (NULL);
	while (i < len)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}
