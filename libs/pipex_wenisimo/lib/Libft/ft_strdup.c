/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 14:04:23 by anurtiag          #+#    #+#             */
/*   Updated: 2023/10/10 11:56:53 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = ft_strlen(s1);
	str = (char *)malloc(sizeof(*str) * (len + 1));
	if (!str)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = 0;
	return (str);
}
// int	main(void)
// {
// 	const char *s = "buenas tardes se8or";
// 	if (!ft_strdup(s))
// 		printf ("No se duplico correctamente\n");
// 	else
// 		printf ("La cadena duplicada es:  %s\n", ft_strdup(s));
// 	return (0);
// }