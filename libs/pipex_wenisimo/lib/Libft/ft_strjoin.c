/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:47:48 by anurtiag          #+#    #+#             */
/*   Updated: 2023/10/23 12:14:18 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *) malloc ((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i + j] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}
// int	main(void)
// {
// 	char	*s1 = "1234567";
// 	char	*s2 = NULL;
// 	int	*dst;

// 	printf("La primera cadena es:%s\n", s1);
// 	printf("La segunda cadena es:%s\n", s2);
// 	dst = strjoin(s1, s2);
// 	if (dst != NULL)
// 		printf("La union de las cadenas es:%s\n", dst);
// 	return (0);
// }
