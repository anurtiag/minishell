/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:37:58 by anurtiag          #+#    #+#             */
/*   Updated: 2023/10/26 06:45:31 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int		ft_printf(char const *format, ...);
int		ft_putchar(int c, int len);
int		ft_putstr(char *s, int len);
int		ft_putnbr(int n, int len);
int		ft_putnbr_u(unsigned int n, int len);

#endif