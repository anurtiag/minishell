/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:32:42 by anurtiag          #+#    #+#             */
/*   Updated: 2023/10/10 10:55:53 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (ft_strlen(needle) == 0 || needle == NULL)
		return ((char *)haystack);
	while ((i < len && haystack[i] != '\0'))
	{
		j = 0;
		if (haystack[i + j] == needle[j])
		{
			while (haystack[i + j] == needle[j] && i + j < len)
			{
				if (needle [j + 1] == '\0')
					return ((char *)haystack + i);
				j++;
			}
		}
		i++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	char	*mio = ft_strnstr("abc", "abcdef", 3);
// 	char	*c = strnstr("abc", "abcdef", 3);

// 	printf("Mi funcion da:----->%s\n\n\n\n", mio);
// 	printf("La funccion da:---->%s\n", c);
// 	return (0);
// }
