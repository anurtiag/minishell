/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:52:08 by anurtiag          #+#    #+#             */
/*   Updated: 2023/11/17 13:14:08 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	data_type(char const *format, size_t i, va_list args, int len);
static int	hexa_calculator_low(size_t number, int len);
static int	hexa_calculator_upp(size_t n, int len);

int	ft_printf(char const *format, ...)
{
	size_t	i;
	va_list	args;
	int		len;

	va_start(args, format);
	i = -1;
	len = 0;
	if (!format)
		return (0);
	while (format[++i] != '\0')
	{
		if (format[i] == 37)
		{
			i++;
			len = data_type(format, i, args, len);
		}
		else
		{
			if (write (1, &format[i], 1) == -1)
				return (len = -1);
			len++;
		}
	}
	va_end(args);
	return (len);
}

static int	data_type(char const *format, size_t i, va_list args, int len)
{
	if (format[i] == 'c')
		len = ft_putchar(va_arg(args, int), len);
	else if (format[i] == 's')
		len = ft_putstr(va_arg(args, char *), len);
	else if (format[i] == 'p')
	{
		write(1, "0x", 2);
		len = hexa_calculator_low(va_arg(args, size_t), len) + 2;
	}
	else if (format[i] == 'i' || format[i] == 'd')
		len = ft_putnbr(va_arg(args, int), len);
	else if (format[i] == 'u')
		len = ft_putnbr_u(va_arg(args, unsigned int), len);
	else if (format[i] == 'x')
		len = hexa_calculator_low(va_arg(args, unsigned int), len);
	else if (format[i] == 'X')
		len = hexa_calculator_upp(va_arg(args, unsigned int), len);
	else if (format[i] == '%')
	{
		write (1, &format[i], 1);
		len++;
	}
	else
		return (len = -1);
	return (len);
}

static int	hexa_calculator_low(size_t n, int len)
{
	char	c;
	char	*base;

	base = "0123456789abcdef";
	if (n > 15)
		len = hexa_calculator_low(n / 16, len);
	c = (base[n % 16]);
	if (write(1, &c, 1) == -1)
		return (len = -1);
	len++;
	return (len);
}

static int	hexa_calculator_upp(size_t n, int len)
{
	char	c;
	char	*base;

	base = "0123456789ABCDEF";
	if (n > 15)
		len = hexa_calculator_upp(n / 16, len);
	c = (base[n % 16]);
	if (write(1, &c, 1) == -1)
		return (len = -1);
	len++;
	return (len);
}
