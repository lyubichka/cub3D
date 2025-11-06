/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:28:08 by veronikalub       #+#    #+#             */
/*   Updated: 2025/11/02 15:06:15 by veronikalub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void free_scene(t_scene *scene)
{
    int i;

    if (!scene)
        return;

    // free textures
    free(scene->textures.north);
    free(scene->textures.south);
    free(scene->textures.west);
    free(scene->textures.east);
    free(scene->textures.sprite);

    // free map grid
    if (scene->map.grid)
    {
        i = 0;
        while (scene->map.grid[i])
        {
            free(scene->map.grid[i]);
            i++;
        }
        free(scene->map.grid);
    }

    free(scene);
}
