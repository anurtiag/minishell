/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:17:05 by anurtiag          #+#    #+#             */
/*   Updated: 2023/09/28 20:06:57 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}

// int main(void)
// {
// 	char c[] = "cadena";
// 	printf ("En la cadena pone: %s\n\n\n", c);
// 	ft_bzero(c, 5);
// 	printf ("y ahora pone: %s\n\n\n", c);
// 	return (0);
// }
