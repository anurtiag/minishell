/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 17:59:45 by anurtiag          #+#    #+#             */
/*   Updated: 2023/10/24 06:42:40 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list	*lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (0);
	else
	{
		while (lst)
		{
			if (!lst->next)
				return (lst);
			lst = lst->next;
			i++;
		}
	}
	return (lst);
}
// int main (void)
// {
// 	t_list	*lst = NULL;
// 	t_list *nodo1 = ft_lstnew("holapepito");
// 	t_list *nodo2 = ft_lstnew("1234567890");
// 	t_list *nodo3 = ft_lstnew("que tal estamos");
// 	ft_lstadd_front(&lst, nodo3);
// 	ft_lstadd_front(&lst, nodo2);
// 	ft_lstadd_front(&lst, nodo1);
// 	t_list *last_node = ft_lstlast(lst);
// 	printf("El ultimo nodo contiene: -->%s<--", last_node->content);
// 	return (0);
// }