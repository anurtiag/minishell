/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 07:13:43 by anurtiag          #+#    #+#             */
/*   Updated: 2023/10/10 11:50:23 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned	int, char))
{
	char			*str;
	unsigned int	i;

	i = 0;
	str = (char *) malloc ((ft_strlen(s) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

/*char	funcion(unsigned int i, char c)
{
	c = c + 1;
	i++;
	return (c);
}*/

// int	main(void)
// {
// 	char	*str;
// 	char	*s = "1234567";

// 	str = ft_strmapi(s, funcion);
// 	printf("%s\n", s);
// 	printf("%s", str);
// 	return (0);
// }
