/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fdl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:01:35 by haiqbal           #+#    #+#             */
/*   Updated: 2025/10/08 16:01:36 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fdl(int n, int fd)
{
	if (n == -2147483648)
	{
		if (write(fd, "-2147483648", 11) == -1)
			return (-1);
		return (0);
	}
	if (n < 0)
	{
		if (ft_putchar_fdl('-', fd) == -1)
			return (-1);
		n = -n;
	}
	if (n >= 10)
	{
		if (ft_putnbr_fdl (n / 10, fd) == -1)
			return (-1);
	}
	if (ft_putchar_fdl(n % 10 + '0', fd) == -1)
		return (-1);
	return (0);
}
