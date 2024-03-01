/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:40:45 by anurtiag          #+#    #+#             */
/*   Updated: 2023/09/29 18:16:54 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*str;
	size_t		i;

	str = (const void *)s;
	i = 0;
	while (i < n)
	{
		if ((unsigned char)str[i] == (unsigned char)c)
			return ((void *) s + i);
		i++;
	}
	return (NULL);
}
// int	main(void)
// {
// 	const char	*s = "Holapepito que tal estamos";
// 	int	letra = '1';
// 	const char *ptr = ft_memchr(s, letra, 20);
// 	if (ptr)
// 		printf ("Encontre la letra %s\n\n\n", ptr);
// 	else
// 		printf ("Pues parece ser que no encontre la letra %s\n\n\n", ptr);
// 	return (0);
// }
