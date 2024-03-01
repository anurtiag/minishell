/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:04:39 by anurtiag          #+#    #+#             */
/*   Updated: 2023/09/28 20:40:23 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
// int	main(void)
// {
// 	if (ft_isascii (48))
// 		printf ("Es un numero \n\n\n");
// 	else
// 		printf ("No es un numero\n\n\n");
// 	return (0);
// }
