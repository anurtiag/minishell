/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 08:04:36 by anurtiag          #+#    #+#             */
/*   Updated: 2023/10/24 06:42:35 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list	*lst, void (*f)(void *))
{
	if (!lst)
		return ;
	else
	{
		while (lst)
		{
			f(lst->content);
			lst = lst->next;
		}
	}
	return ;
}

// void	function(char *content)
// {
// 	content -= 32;
// 	return (content);
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
// 	printf("La lista tiene %i nodos\n", ft_lstsize(lst));
// 	if (lst)
// 		ft_lstiter(lst, function);
// 	while (lst != NULL)
// 	{
// 		printf("%s\n", lst->content);
// 		lst = lst->next;
// 	}
// 	return (0);
// }
