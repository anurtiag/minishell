/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calculator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:47:48 by anurtiag          #+#    #+#             */
/*   Updated: 2023/10/26 06:46:10 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_putchar(int c, int len)
{
	if (write(1, &c, 1) == -1)
		return (len = -1);
	len++;
	return (len);
}

int	ft_putstr(char *s, int len)
{
	size_t	i;

	i = 0;
	if (!s)
	{
		if (write (1, "(null)", 6) == -1)
			return (len = -1);
		len = len + 6;
		return (len);
	}
	while (s[i] != '\0')
	{
		if (write(1, &s[i], 1) == -1)
			return (len = -1);
		i++;
		len++;
	}
	return (len);
}

int	ft_putnbr(int n, int len)
{
	char	c;

	if (n == -2147483648)
	{
		if (write (1, "-2147483648", 11) == -1)
			return (len = -1);
		len = len + 11;
		return (len);
	}
	else if (n < 0)
	{
		n = n * -1;
		if (write (1, "-", 1) == -1)
			return (len = -1);
		len++;
	}
	if (n > 9)
		len = ft_putnbr(n / 10, len);
	c = (n % 10 + 48);
	if (write(1, &c, 1) == -1)
		return (len = -1);
	len++;
	return (len);
}

int	ft_putnbr_u(unsigned int n, int len)
{
	char	c;

	if (n > 9)
		len = ft_putnbr(n / 10, len);
	c = (n % 10 + 48);
	if (write(1, &c, 1) == -1)
		return (len = -1);
	len++;
	return (len);
}

int	ft_putnbr_d(int n, int len)
{
	char	c;

	if (n == -2147483648)
	{
		if (write (1, "-2147483648", 11) == -1)
			return (len = -1);
		len = len + 11;
		return (len);
	}
	else if (n < 0)
	{
		n = n * -1;
		if (write (1, "-", 1) == -1)
			return (len = -1);
		len++;
	}
	if (n > 9)
		len = ft_putnbr(n / 10, len);
	c = (n % 10 + 48);
	if (write(1, &c, 1) == -1)
		return (len = -1);
	len++;
	return (len);
}
