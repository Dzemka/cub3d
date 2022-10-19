/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 06:56:58 by olugash           #+#    #+#             */
/*   Updated: 2021/10/22 06:57:00 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*clear(t_list **list, void *del_f)
{
	ft_lstclear (list, del_f);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_elem;
	t_list	*new_list;

	if (lst == NULL)
		return (NULL);
	new_elem = ft_lstnew(f(lst->content));
	if (new_elem == NULL)
		return (clear(&new_elem, del));
	new_list = new_elem;
	lst = lst->next;
	while (lst != NULL)
	{
		new_elem = ft_lstnew(f(lst->content));
		if (new_elem == NULL)
			return (clear(&new_list, del));
		ft_lstadd_back(&new_list, new_elem);
		new_elem = new_elem->next;
		lst = lst->next;
	}
	return (new_list);
}
