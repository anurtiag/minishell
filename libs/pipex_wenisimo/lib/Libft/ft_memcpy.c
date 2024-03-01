/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:50:03 by anurtiag          #+#    #+#             */
/*   Updated: 2023/10/09 10:29:33 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*dest;
	char	*source;

	i = 0;
	dest = ((char *)dst);
	source = ((char *)src);
	if (dst == src || (n == 0))
		return (dst);
	while (i < n)
	{
		dest[i] = source[i];
		i++;
	}
	return (dst);
}
// int	main(void)
// {
// 	const char	*s1 = "Holapep8ito que tal estamos";
// 	char	s2[30] = "Esto se va a borrar";
// 	s2[30] = '\0';
// 	s2 = ft_memcpy(s2, s1, 20);
// 	printf ("La copia es:  %s\n\n\n", s2);
// 	return (0);
// }
