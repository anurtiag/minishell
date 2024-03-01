/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:33:42 by anurtiag          #+#    #+#             */
/*   Updated: 2023/10/24 06:42:30 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	del(void *content);

void	ft_lstdelone(t_list	*lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	else
	{
		del(lst->content);
		free (lst);
	}
}

// void	del(void *content)
// {
// 	*(char *)content = 0;
// }

// int main (void)
// {
// 	t_list	*lst;
// 	t_list	**test;

// 	lst = 0;
// 	test = &(lst);
// 	ft_lstadd_back(test, ft_lstnew("hola"));
// 	ft_lstadd_back(test, ft_lstnew("pepito"));
// 	ft_lstadd_back(test, ft_lstnew("que"));
// 	ft_lstadd_back(test, ft_lstnew("tal"));
// 	printf("El tamaño del nodo es: -->%d<--\n", ft_lstsize(lst));
// 	ft_lstdelone(&(test[0]->next), del);
// 	printf("El tamaño del nodo es: -->%d<--\n", ft_lstsize(lst));
// 	return (0);
// }
