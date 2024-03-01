/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:29:56 by anurtiag          #+#    #+#             */
/*   Updated: 2023/10/16 15:24:51 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		cal_digit(int n);
static char		*num_is_negative(int n, char *num, int digit);
static char		*num_is_positive(int n, char *num, int digit);

char	*ft_itoa(int n)
{
	char	*num;
	int		digit;

	digit = 0;
	num = NULL;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		num = num_is_negative(n, num, digit);
		return (num);
	}
	else
	{
		num = num_is_positive(n, num, digit);
		return (num);
	}
}

static char	*num_is_negative(int n, char *num, int digit)
{
	n = n * -1;
	digit = cal_digit(n) + 1;
	num = (char *) malloc ((digit + 1) * sizeof(char));
	if (num == NULL)
		return (NULL);
	num[0] = 45;
	num[digit] = '\0';
	while (digit > 1)
	{
		num[digit -1] = (n % 10) + '0';
		n = n / 10;
		digit--;
	}
	return (num);
}

static char	*num_is_positive(int n, char *num, int digit)
{
	digit = cal_digit(n);
	num = (char *) malloc ((digit + 1) * sizeof(char));
	if (num == NULL)
		return (NULL);
	num[digit] = '\0';
	if (n == 0)
	{
		num[0] = 48;
	}
	while (digit >= 1)
	{
		num[digit -1] = (n % 10) + '0';
		n = n / 10;
		digit--;
	}
	return (num);
}

static int	cal_digit(int n)
{
	int	i;

	i = 1;
	while (n / 10 != 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

// int	main(void)
// {
// 	char	*str;
// 	int		n;

// 	n = 98;
// 	str = ft_itoa(n);
// 	printf("El numero es:---->%i\n\n\n\n", n);
// 	printf("El numero es:---->%s", str);
// 	printf("\n");
// 	free (str);
// 	return (0);
// }
