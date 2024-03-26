/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:33:13 by emimenza          #+#    #+#             */
/*   Updated: 2024/03/26 09:42:35 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Allocates (with malloc(3)) and returns a new
// string, which is the result of the concatenation
// of ’s1’ and ’s2’. With mode 3 free s1, with 5 s2,
//with 15 both and with 1 nothing

char	*ft_strjoin(char const *s1, char const *s2, int mode)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	str = (char *) malloc ((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
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
	if (mode % 3 == 0)
		free((char *)s1);
	if (mode % 5 == 0)
		free((char *)s2);
	return (str);
}
