/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:12:58 by olugash           #+#    #+#             */
/*   Updated: 2021/10/19 16:13:00 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_new_str;
	char	*str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	str = NULL;
	len_new_str = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (char *)malloc(sizeof(char) * (len_new_str));
	if (str == NULL)
		return (NULL);
	(void)ft_strlcpy(str, s1, len_new_str);
	(void)ft_strlcat(str, s2, len_new_str);
	return (str);
}
