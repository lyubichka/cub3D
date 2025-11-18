/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 16:15:39 by veronikalub       #+#    #+#             */
/*   Updated: 2025/11/16 19:15:48 by veronikalub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static int  is_byte(const char *s)
{
    int i;

    if (!s || !*s)
        return (0);
    i = 0;
    while (s[i])
    {
        if (s[i] < '0' || s[i] > '9')
            return (0);
        i++;
    }
    return (1);
}

static void trim_parts(char **parts)
{
    int   k;
    char *t;

    k = 0;
    while (k < 3 && parts[k])
    {
        t = ft_strtrim(parts[k], " \t");
        free(parts[k]);
        parts[k] = t;
        k++;
    }
}

void parse_rgb(char **parts, int out[3])
{
    int r;
    int g;
    int b;

    trim_parts(parts);
    if (!is_byte(parts[0]) || !is_byte(parts[1]) || !is_byte(parts[2]))
    {
        free_split(parts);
        print_error("Color components must be integers");
    }
    r = ft_atoi(parts[0]);
    g = ft_atoi(parts[1]);
    b = ft_atoi(parts[2]);
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
    {
        free_split(parts);
        print_error("Color components must be in [0,255]");
    }
    out[0] = r;
    out[1] = g;
    out[2] = b;
    free_split(parts);
}
