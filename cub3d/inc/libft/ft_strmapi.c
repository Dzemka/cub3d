/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 19:15:26 by olugash           #+#    #+#             */
/*   Updated: 2021/10/20 19:15:30 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			len_s;
	char			*new_str;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	len_s = ft_strlen(s);
	new_str = (char *)(malloc(sizeof(char) * (len_s + 1)));
	if (new_str == NULL)
		return (NULL);
	while (i < len_s)
	{
		new_str[i] = f(i, s[i]);
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
