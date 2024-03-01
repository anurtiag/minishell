/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:39:52 by anurtiag          #+#    #+#             */
/*   Updated: 2023/10/10 11:17:12 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		str[i] = c;
		i++;
	}
	return (b);
}

// int	main(void)
// {
// 	char *s = "esta primera parte se va a borrar";
// 	int	c = 111;
// 	size_t	len = 7;
// 	ft_memset(s, c, len);
// 	printf("La cadena modificada es:  %s", s);
// 	return (0);
// }
