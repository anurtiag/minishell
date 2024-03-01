/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:38:02 by anurtiag          #+#    #+#             */
/*   Updated: 2023/11/17 10:48:51 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if ((unsigned char)s1[i] > (unsigned char)s2[i])
		{
			return (1);
		}
		else if ((unsigned char)s1[i] < (unsigned char)s2[i])
		{
			return (-1);
		}
		i++;
	}
	return (0);
}
// int	main(void)
// {
// 	char	*s1 = "1234567";
// 	char	*s2 ="1234567";
// 	int		dst = 0;

// 	printf("La primera cadena es:%s\n", s1);
// 	printf("La segunda cadena es:%s\n", s2);
// 	dst = ft_strncmp(s1, s2, 10);
// 	if (dst > 0)
// 		printf("La cadena 1 es mayor");
// 	else if (dst < 0)
// 		printf("La cadena 2 es mayor");
// 	else if (dst == 0)
// 		printf("Las cadenas son iguales");
// 	return (0);
// }
