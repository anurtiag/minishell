/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 07:53:19 by anurtiag          #+#    #+#             */
/*   Updated: 2023/12/15 08:25:12 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static size_t		num_strings(char const *s, char c);

static char	**freeall(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	i;
	size_t	len;
	size_t	start;

	i = 0;
	len = 0;
	start = 0;
	str = (char **) ft_calloc ((num_strings(s, c) + 1), sizeof (char *));
	if (!str)
		return (NULL);
	while (i < num_strings(s, c))
	{
		while (s[len] == c)
			len++;
		start = len;
		while (s[len] != c && len < ft_strlen(s))
			len++;
		str[i] = ft_substr(s, start, (len - start));
		if (str[i] == NULL)
			return (freeall(str));
		i++;
	}
	return (str);
}

static size_t	num_strings(char const *s, char c)
{
	size_t	i;
	int		div;

	div = 0;
	i = 0;
	if (c == 0 && *s != 0)
		return (1);
	else if (c == 0)
		return (0);
	while (s[i] == c)
		i++;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			div++;
		i++;
	}
	return (div);
}

// int	main(void)
// {
// 	char	*palabra = "      split       this for   me  !       ";
// 	char	c = ' ';
// 	char	**str;
// 	int		i = 0;

// 	str = ft_split(palabra, c);
// 	printf("PALABRAS: %zu\n\n", num_strings(palabra, c));
// 	while (str[i])
// 	{
// 		printf("LINEA: %i - %s\n", i, str[i]);
// 		i++;
// 	}
// 	return (0);
// }
