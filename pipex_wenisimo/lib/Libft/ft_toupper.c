/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 07:59:25 by anurtiag          #+#    #+#             */
/*   Updated: 2023/09/29 18:31:08 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
	{
		c = c - 32;
		return (c);
	}
	else
		return (c);
}
// int	main(void)
// {
// 	int c = 99;
// 	char a = ft_toupper(c);
// 	printf("la letra antes era %c y ahora es %c\n\n", c, a);
// 	return (0);
// }