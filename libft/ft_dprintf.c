/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:00:45 by haiqbal           #+#    #+#             */
/*   Updated: 2025/10/08 16:00:48 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	printf_test(int fd, va_list flags, const char *string, int i)
{
	int	printed;
	int	t;

	t = 0;
	printed = 0;
	if (string[i] == 'c')
		printed = ft_putchar_fdl(va_arg(flags, int), fd);
	if (string[i] == 's')
		printed = ft_putstr_fdl(va_arg(flags, char *), fd);
	if (string[i] == 'd' || string[i] == 'i')
		printed = ft_putnbr_fdl(va_arg(flags, int), fd);
	if (string[i] == 'u')
		printed = ft_putnbr_u_fd(va_arg(flags, unsigned int), fd);
	if (string[i] == 'x' || string[i] == 'X')
		printed = ft_puthex_fd(va_arg(flags, unsigned int), string[i], &t, fd);
	if (string[i] == 'p')
		printed = ft_putmem_fd(va_arg(flags, size_t), &t, fd);
	if (string[i] == '%')
		printed = ft_putchar_fdl('%', fd);
	if (printed == -1)
		return (-1);
	if (string[i] != 'x' && string[i] != 'X')
		t += printed;
	return (t);
}

int	ft_dprintf(int fd, const char *string, ...)
{
	va_list	flags;
	int		i;
	int		total_chars;

	i = 0;
	va_start(flags, string);
	while (string[i] != '\0')
	{
		if (string[i] == '%')
		{
			i++;
			total_chars = printf_test(fd, flags, string, i);
			if (total_chars == -1)
				return (-1);
			i++;
		}
		else
		{
			if (ft_putchar_fdl(string[i], fd) == -1)
				return (-1);
			total_chars++;
			i++;
		}
	}
	return (total_chars);
}
