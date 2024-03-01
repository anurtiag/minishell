/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:19:18 by anurtiag          #+#    #+#             */
/*   Updated: 2023/09/28 20:26:10 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*output;

	output = malloc(count * size);
	if (output == NULL)
		return (NULL);
	ft_bzero(output, count * size);
	return (output);
}

// int main (void)
// {
// 	size_t	a = 7;
// 	size_t	b = 8;
// 	printf ("El numero en la string es: %s\n\n\n",ft_calloc(a, b));
// 	return (0);
// }