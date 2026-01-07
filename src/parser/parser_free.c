/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:28:08 by veronikalub       #+#    #+#             */
/*   Updated: 2026/01/02 14:43:44 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	free_scene(t_scene *scene)
{
	int	i;

	if (!scene)
		return ;
	free(scene->textures.north);
	free(scene->textures.south);
	free(scene->textures.west);
	free(scene->textures.east);
	if (scene->map.grid)
	{
		i = 0;
		while (i < scene->map.height)
		{
			free(scene->map.grid[i]);
			i++;
		}
		free(scene->map.grid);
	}
}

void	free_full_scene(t_scene *scene)
{
	if (!scene)
		return ;
	free_scene(scene);
	free(scene);
}
