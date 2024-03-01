/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:31:56 by anurtiag          #+#    #+#             */
/*   Updated: 2023/10/10 10:59:06 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*str;

	str = (char *)s;
	i = (ft_strlen (str));
	str += i;
	while (i > 0)
	{
		if (*str == (unsigned char)c)
			return (str);
		str--;
		i--;
	}
	if (*str == (unsigned char)c)
		return (str);
	return (NULL);
}

// int	main(void)
// {
// 	const char *s = "bue8nas tardes se8or";
// 	int	c = 56;
// 	if (!ft_strrchr(s, c))
// 		printf ("No hay equivalencias\n");
// 	else
// 		printf ("La equivalencia es:  %s\n", ft_strrchr(s, c));
// 	return (0);
// }
