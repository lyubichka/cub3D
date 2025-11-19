/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:27:46 by veronikalub       #+#    #+#             */
/*   Updated: 2025/11/18 20:07:46 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

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