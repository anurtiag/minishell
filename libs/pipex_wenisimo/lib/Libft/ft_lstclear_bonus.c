/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 19:28:34 by anurtiag          #+#    #+#             */
/*   Updated: 2023/10/24 06:46:41 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list	**lst, void (*del)(void *))
{
	t_list	*node;

	if (!lst || !del)
		return ;
	if (*lst)
	{
		while (*lst)
		{
			node = (*lst);
			*lst = (*lst)->next;
			del(node->content);
			free(node);
		}
		return ;
	}
}

// void	delete(void *content)
// {
// 	*(char *)content = 0;
// }

// int	main(void)
// {
// 	t_list	*lst;
// 	t_list	**test;

// 	lst = 0;
// 	test = &(lst);
// 	ft_lstadd_back(test, ft_lstnew("hola"));
// 	ft_lstadd_back(test, ft_lstnew("pepito"));
// 	ft_lstadd_back(test, ft_lstnew("que"));
// 	ft_lstadd_back(test, ft_lstnew("tal"));
// 	printf("La lista tiene %i nodes\n", ft_lstsize(lst));
// 	if (lst)
// 		ft_lstclear(test, delete);
// 	printf("La lista tiene %i nodes\n", ft_lstsize(lst));
// 	return (0);
// }
