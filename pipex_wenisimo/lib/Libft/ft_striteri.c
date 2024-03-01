/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:21:32 by anurtiag          #+#    #+#             */
/*   Updated: 2023/10/10 11:50:16 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned	int, char*))
{
	unsigned int	i;

	i = 0;
	if (s == NULL || f == NULL)
		return ;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}
/*
void	funcion(unsigned int i, char *c)
{
		*c = *c + 1;
		i++;
}*/

// int	main(void)
// {
// 	char	*s = "1234567";
// 	char	*str;

// 	str = ft_strdup(s);
// 	printf("La cadena antes de modificar es:%s\n", s);
// 	ft_striteri(str, funcion);
// 	printf("La nueva cadena es:%s\n", str);
// 	return (0);
// }
