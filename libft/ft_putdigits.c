/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdigits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:14:50 by hajmoham          #+#    #+#             */
/*   Updated: 2025/10/08 12:15:37 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_putnbr(int num)
{
	ssize_t	length;

	length = 0;
	if (num == -2147483648)
	{
		length += ft_putstr("-2147483648");
	}
	else if (num < 0)
	{
		length += ft_putchar('-');
		length += ft_putnbr(-num);
	}
	else if (num > 9)
	{
		length += ft_putnbr(num / 10);
		length += ft_putchar('0' + num % 10);
	}
	else
	{
		length += ft_putchar('0' + num);
	}
	return (length);
}

ssize_t	ft_putunbr(unsigned int num)
{
	ssize_t	length;

	length = 0;
	if (num > 9)
	{
		length += ft_putunbr(num / 10);
		length += ft_putchar('0' + num % 10);
	}
	else
	{
		length += ft_putchar('0' + num);
	}
	return (length);
}

ssize_t	ft_puthex(unsigned long long num, char format)
{
	ssize_t	length;

	length = 0;
	if (num >= 16)
	{
		length += ft_puthex(num / 16, format);
		length += ft_puthex(num % 16, format);
	}
	else
	{
		if (num >= 10)
		{
			if (format == 'X')
				length += ft_putchar(num - 10 + 'A');
			else if (format == 'x')
				length += ft_putchar(num - 10 + 'a');
		}
		else
		{
			length += ft_putchar(num + '0');
		}
	}
	return (length);
}

ssize_t	ft_putptr(void *ptr)
{
	ssize_t	length;

	length = 0;
	length += ft_putstr("0x");
	length += ft_puthex((unsigned long long)ptr, 'x');
	return (length);
}
