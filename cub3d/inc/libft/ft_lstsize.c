/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 15:07:26 by olugash           #+#    #+#             */
/*   Updated: 2021/10/21 15:07:28 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count_elem;

	count_elem = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		count_elem++;
	}
	return (count_elem);
}
