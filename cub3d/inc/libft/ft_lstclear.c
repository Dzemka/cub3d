/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 04:50:09 by olugash           #+#    #+#             */
/*   Updated: 2021/10/22 04:50:12 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*p;
	t_list	*temp;

	p = *lst;
	while (p != NULL)
	{
		temp = p->next;
		del(p->content);
		free(p);
		p = temp;
	}
	*lst = NULL;
}
