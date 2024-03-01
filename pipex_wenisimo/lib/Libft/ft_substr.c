/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 09:58:44 by anurtiag          #+#    #+#             */
/*   Updated: 2023/10/22 19:33:10 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;

	if (!s)
		return (ft_strdup(""));
	if (start > ft_strlen(s) || len == 0)
		return (ft_strdup(""));
	if (ft_strlen((char *)s) - start < len)
		len = ft_strlen((char *)s) - start;
	str = (char *) malloc (sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, s + start, len);
	str[len] = '\0';
	return (str);
}

// int main(void)
// {
// 	char *a = ft_substr(NULL, 0, 9);
// 	int i = 0;
//     if (a == NULL)
//     {
//     	printf("ha dado NULL\n");
//     }
//     else
//     {
// 		while (a[i] != '\0')
// 		{
// 			printf("%c", a[i]);
// 			i++;
// 		}
// 	}
// 	free (a);
// 	return (0);
// }
