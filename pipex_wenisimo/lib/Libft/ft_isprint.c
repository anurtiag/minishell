/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:35:03 by anurtiag          #+#    #+#             */
/*   Updated: 2023/09/28 20:40:45 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}
// int	main(void)
// {
// 	if (ft_isascii (48))
// 		printf ("Es printeable \n\n\n");
// 	else
// 		printf ("No es printeable\n\n\n");
// 	return (0);
// }
