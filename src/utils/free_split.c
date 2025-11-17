/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:27:46 by veronikalub       #+#    #+#             */
/*   Updated: 2025/10/30 16:59:24 by veronikalub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void free_split(char **parts)
{
    int i;

    if (!parts)
        return;
    i = 0;
    while (parts[i])
    {
        free(parts[i]);
        i++;
    }
    free(parts);
}