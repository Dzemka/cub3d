/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olugash <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 22:31:09 by olugash           #+#    #+#             */
/*   Updated: 2021/10/20 22:31:11 by olugash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_elem;

	new_elem = (t_list *)(malloc(sizeof(t_list)));
	if (new_elem == NULL)
		return (NULL);
	new_elem -> content = content;
	new_elem -> next = NULL;
	return (new_elem);
}
