/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:19:55 by anurtiag          #+#    #+#             */
/*   Updated: 2023/10/10 11:56:31 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	contador;

	i = 0;
	contador = ft_strlen (src);
	if (dstsize != 0)
	{
		while (src[i] != '\0' && i < (dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (contador);
}
// int	main(void)
// {
// 	char	s1[10] = "hello";
// 	size_t	n = 0;
// 	n = ft_strlcat(s1, "cat", 0);
// 	printf("La longitud de las dos cadenas es:%zu\n", n);
// 	return (0);
// }
