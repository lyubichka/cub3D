/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putsc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:15:16 by hajmoham          #+#    #+#             */
/*   Updated: 2025/10/08 12:15:45 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

ssize_t	ft_putstr(char *str)
{
	ssize_t	i;
	ssize_t	length;

	length = 0;
	i = 0;
	if (!str)
		str = "(null)";
	while (str[i])
	{
		length += ft_putchar(str[i]);
		i++;
	}
	return (length);
}
