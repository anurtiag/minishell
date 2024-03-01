/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:00:39 by anurtiag          #+#    #+#             */
/*   Updated: 2023/10/19 06:46:18 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n == -2147483648)
	{
		write (fd, "-2147483648", 11);
		return ;
	}
	else if (n < 0)
	{
		n = n * -1;
		write (fd, "-", 1);
	}
	if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	c = (n % 10 + 48);
	write (fd, &c, 1);
	return ;
}
// int	main(void)
// {
// 	ft_putnbr_fd(-21474836, 2);
// 	return (0);
// }
