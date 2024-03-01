/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 09:13:11 by anurtiag          #+#    #+#             */
/*   Updated: 2023/12/15 08:24:30 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	signo;
	int	num;

	i = 0;
	num = 0;
	signo = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		signo = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num * signo);
}
// int	main(void)
// {
// 	const char numero[] = "14574drgrd6";
// 	int num = ft_atoi(numero);
// 	printf ("El numero en la string es: %s\n\n\n",numero);
// 	printf ("El numero en int es: %i\n\n\n",num);
// 	return (0);
// }