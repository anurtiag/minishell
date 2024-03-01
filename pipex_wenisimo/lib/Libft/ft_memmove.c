/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:58:53 by anurtiag          #+#    #+#             */
/*   Updated: 2023/10/10 11:17:01 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*dest;
	char	*source;

	i = 0;
	dest = ((char *)dst);
	source = ((char *)src);
	if (dest == source)
		return (dest);
	if (dest > source)
	{
		while (len -- > 0)
			dest[len] = source[len];
	}
	else
	{
		while (i < len)
		{
			dest[i] = source[i];
			i++;
		}
	}
	return (dest);
}
// int	main(void)
// {
// 	char	*s1 = "Holapep8ito que tal estamos";
// 	char	*s2 = "Esto se va a borrar";
// 	ft_memmove(s2, s1, 20);
// 	printf ("La copia es:  %s\n\n\n", s2);
// 	return (0);
// }
