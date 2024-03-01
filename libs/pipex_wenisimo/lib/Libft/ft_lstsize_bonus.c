/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:08:32 by anurtiag          #+#    #+#             */
/*   Updated: 2023/10/24 06:43:05 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list	*lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (0);
	else
	{
		while (lst)
		{
			lst = lst->next;
			i++;
		}
	}
	return (i);
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
// 	int len = ft_lstsize(lst);
// 	printf("El tamaño del nodo es: -->%i<--", len);
// 	return (0);
// }