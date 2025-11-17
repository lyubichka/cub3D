/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:59:19 by veronikalub       #+#    #+#             */
/*   Updated: 2025/11/16 19:42:57 by veronikalub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void print_error(const char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd((char *)msg, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

int	is_number_str(const char *s)
{
    int i;

    if (!s || !*s)
        return (0);
    i = 0;
    while (s[i])
    {
        if (!(s[i] >= '0' && s[i] <= '9'))
            return (0);
        i++;
    }
    return (1);
}

static int	get_max_width(char **lines, int start, int end)
{
    int	max = 0;
    int	len;

	while (start < end)
	{
		len = ft_strlen(lines[start]);
		if (len > max)
			max = len;
		start++;
	}
	    return (max);
}

static int is_player(char c)
{
    return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}