/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:31:06 by anurtiag          #+#    #+#             */
/*   Updated: 2023/10/24 06:42:20 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list	**lst, t_list	*new)
{
	if (lst)
	{
		if (*lst)
			new->next = *lst;
		*lst = new;
	}
}
// int main (void)
// {
// 	t_list	*lst = NULL;
// 	t_list *nodo = ft_lstnew("holapepito");
// 	ft_lstadd_front(&lst, nodo);
// 	printf("El primer nodo ahoora es: -->%s<--", lst->content);
// 	return (0);
// }