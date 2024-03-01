/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:20:33 by anurtiag          #+#    #+#             */
/*   Updated: 2023/09/28 20:37:42 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}

// int	main(void)
// {
// 	if (ft_isascii (48))
// 		printf ("Es parte del Ascii \n\n\n");
// 	else
// 		printf ("No es parte del Ascii\n\n\n");
// 	return (0);
// }
