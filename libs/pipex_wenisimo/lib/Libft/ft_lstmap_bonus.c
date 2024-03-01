/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 08:19:01 by anurtiag          #+#    #+#             */
/*   Updated: 2023/10/24 06:42:46 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list	*lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node1;
	t_list	*node2;
	t_list	*node3;

	if (!lst)
		return (NULL);
	node1 = ft_lstnew(f(lst->content));
	node2 = node1;
	node3 = lst;
	lst = lst->next;
	while (lst)
	{
		node1->next = ft_lstnew(f(lst->content));
		if (node1->next == NULL)
			ft_lstclear(&node3, del);
		node1 = node1->next;
		lst = lst->next;
	}
	return (node2);
}
