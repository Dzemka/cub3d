/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 16:44:13 by olugash           #+#    #+#             */
/*   Updated: 2021/10/16 16:44:15 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_strings(char *str, char divider)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] != divider && (str[i + 1] == divider || str[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static int	ft_len_string(char *str, char divider, int index)
{
	int	len;

	len = 0;
	while (str[index] != divider && str[index] != '\0')
	{
		index++;
		len++;
	}
	return (len);
}

static char	**clear_leaks(char **dst, int s_index)
{
	int	clean_s_index;

	clean_s_index = 0;
	while (clean_s_index < s_index)
	{
		free(dst[clean_s_index]);
		clean_s_index++;
	}
	free(dst);
	return (NULL);
}

static char	**fill_td_array(char **dst, char *src, char divider, int count_str)
{
	int	s_index;
	int	c_index;
	int	len_string;
	int	src_index;

	s_index = 0;
	len_string = 0;
	src_index = 0;
	while (s_index < count_str)
	{
		c_index = 0;
		while (src[src_index] == divider)
			src_index++;
		len_string = ft_len_string(src, divider, src_index);
		dst[s_index] = (char *)(malloc(sizeof(char) * (len_string + 1)));
		if (dst[s_index] == NULL)
			return (clear_leaks(dst, s_index));
		while (c_index < len_string)
			dst[s_index][c_index++] = src[src_index++];
		dst[s_index++][c_index] = '\0';
	}
	dst[s_index] = NULL;
	return (dst);
}

char	**ft_split(char const *s, char c)
{
	char	**ss;
	int		count_strings;

	if (s == NULL)
		return (NULL);
	count_strings = ft_count_strings((char *)s, c);
	ss = (char **)(malloc(sizeof(char *) * (count_strings + 1)));
	if (ss == NULL)
		return (NULL);
	ss = fill_td_array(ss, (char *)s, c, count_strings);
	if (ss == NULL)
		return (NULL);
	return (ss);
}
