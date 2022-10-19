/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 19:47:31 by olugash           #+#    #+#             */
/*   Updated: 2021/10/14 19:47:33 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		sign;
	long	res;

	sign = 1;
	res = 0;
	while ((*str >= '\t' && *str <= '\r') || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str != '\0' && ft_isdigit(*str) != 0)
		res = *str++ + res * 10 - 48;
	if (res < 0)
	{
		if (sign < 0)
			return (0);
		else
			return (-1);
	}
	return (res * sign);
}
