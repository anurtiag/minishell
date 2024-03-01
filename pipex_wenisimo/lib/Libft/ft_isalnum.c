/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:53:14 by anurtiag          #+#    #+#             */
/*   Updated: 2023/09/28 20:32:05 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && \
	c <= 'Z') || (c >= '0' && c <= '9'))
		return (1);
	else
		return (0);
}

// int	main(void)
// {
// 	if (ft_isalnum (48))
// 		printf ("Es un numero o una letra\n\n\n");
// 	else
// 		printf ("No es un numero o una letra\n\n\n");
// 	return (0);
// }
