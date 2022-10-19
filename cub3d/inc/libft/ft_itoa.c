/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:26:58 by olugash           #+#    #+#             */
/*   Updated: 2021/10/23 23:18:44 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_lenght(int n)
{
	int	lenght;

	if (n == '\0')
		return (1);
	lenght = 0;
	if (n == -2147483648)
	{
		n = 147483648;
		lenght = 2;
	}
	else if (n < 0)
	{
		n = -n;
		lenght++;
	}
	while (n != 0)
	{
		lenght++;
		n = n / 10;
	}
	return (lenght);
}

static int	check_discharge(int number)
{
	int	discharge;

	discharge = 1;
	while (number / 10 != 0)
	{
		number = number / 10;
		discharge = discharge * 10;
	}
	return (discharge);
}

static void	fill_str(int n, int j, int discharge, char *str)
{
	while (discharge > 0)
	{
		str[j++] = n / discharge + 48;
		n = n % discharge;
		discharge = discharge / 10;
	}
	str[j] = '\0';
}

char	*ft_itoa(int n)
{
	char	*str;
	int		j;

	j = 0;
	str = NULL;
	str = (char *)malloc(sizeof(char) * (check_lenght(n) + 1));
	if (str == NULL)
		return (NULL);
	if (n == -2147483648)
	{
		str[j++] = '-';
		str[j++] = '2';
		n = 147483648;
	}
	else if (n < 0)
	{
		str[j++] = '-';
		n = -n;
	}
	fill_str(n, j, check_discharge(n), str);
	return (str);
}
