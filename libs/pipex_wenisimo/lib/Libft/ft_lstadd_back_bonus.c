/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:05:22 by anurtiag          #+#    #+#             */
/*   Updated: 2023/10/24 06:46:23 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list	**lst, t_list *new)
{
	t_list	*node;

	if (lst && *lst)
	{
		node = ft_lstlast(*lst);
		node->next = new;
	}
	else
		*lst = new;
}
// int main (void)
// {
// 	t_list	*lst = NULL;
// 	t_list *node1 = ft_lstnew("holapepito");
// 	t_list *node2 = ft_lstnew("1234567890");
// 	t_list *node3 = ft_lstnew("que tal estamos");
// 	ft_lstadd_back(&lst, node1);
// 	ft_lstadd_back(&lst, node2);
// 	ft_lstadd_back(&lst, node3);
// 	while (lst != NULL)
// 	{
// 		printf("%s\n", lst->content);
// 		lst = lst->next;
// 	}
// 	return (0);
// }