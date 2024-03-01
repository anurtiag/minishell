/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:58:24 by anurtiag          #+#    #+#             */
/*   Updated: 2023/09/29 18:17:32 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (str1[i] != str2[i])
			return ((int)str1[i] - (int)str2[i]);
		i++;
	}
	return (0);
}
// int	main(void)
// {
// 	const char	*s1 = "Holapep8ito que tal estamos";
// 	const char	*s2 = "Holapep7ito que tal estamos";
// 	int		result = ft_memcmp(s1, s2, 20);
// 	if (result > 0)
// 		printf ("La primera cadena es mayor\n\n\n");
// 	else if (result == 0)
// 		printf ("Las cadenas son iguales\n\n\n");
// 	else
// 		printf ("La segunda cadena es mayor\n\n\n");
// 	result (0);
// }
