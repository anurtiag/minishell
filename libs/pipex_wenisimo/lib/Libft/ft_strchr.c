/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 08:32:25 by anurtiag          #+#    #+#             */
/*   Updated: 2023/10/10 10:59:31 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (*str != '\0')
	{
		if (*str == (unsigned char)c)
			return (str);
		str++;
	}
	if (*str == (unsigned char)c)
		return (str);
	return (NULL);
}

// int	main(void)
// {
// 	const char *s = "bue8nas tardes se8or";
// 	int	c = 56;
// 	if (!ft_strchr(s, c))
// 		printf ("No hay equivalencias\n");
// 	else
// 		printf ("La equivalencia es:  %s\n", ft_strchr(s, c));
// 	return (0);
// }