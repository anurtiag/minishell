/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:56:54 by anurtiag          #+#    #+#             */
/*   Updated: 2023/10/10 12:01:53 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_equivalences1(char const *s1, char const *set);
static size_t	ft_equivalences2(char const *s1, char const *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	len;
	size_t	start;

	if (s1 == NULL || set == NULL)
		return (NULL);
	if (ft_equivalences1(s1, set) >= ft_strlen(s1) || \
	ft_equivalences2(s1, set) >= ft_strlen(s1))
		return (ft_strdup(""));
	start = ft_equivalences1(s1, set);
	len = ft_strlen(s1) - ft_equivalences2(s1, set) - start;
	str = ft_substr(s1, start, len);
	if (str == NULL)
	{
		free((void *)str);
		return (NULL);
	}
	return (str);
}

static size_t	ft_equivalences1(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	j;

	i = 0;
	start = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		j = 0;
		while (set[j] != '\0' && start == i)
		{
			if (s1[i] == set[j])
				start++;
			j++;
		}
		i++;
		if (start != i)
			return (start);
	}
	return (0);
}

static size_t	ft_equivalences2(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	j;
	size_t	len;

	len = (ft_strlen (s1) - 1);
	start = 0;
	j = 0;
	i = 0;
	while ((len - i) >= 0)
	{
		j = 0;
		while (set[j] != '\0' && start == i)
		{
			if (s1[len - i] == set[j])
				start++;
			j++;
		}
		i++;
		if (start != i)
			return (start);
	}
	return (0);
}

// int	main(void)
// {
// 	char	*num;

// 	num = ft_strtrim("lorem ipsum dolor sit amet", "tel");
// 	if (num == NULL)
// 	{
// 		printf("ha dado NULL\n");
// 	}
// 	else
// 		printf("la cadena es %s\n", num);
// 	free(num);
// 	return (0);
// }
