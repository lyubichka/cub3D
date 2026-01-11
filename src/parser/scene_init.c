/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 20:00:00 by haiqbal           #+#    #+#             */
/*   Updated: 2026/01/11 20:08:46 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	init_scene_defaults(t_scene *scene)
{
	scene->screen_width = 1280;
	scene->screen_height = 720;
	scene->textures.north = NULL;
	scene->textures.south = NULL;
	scene->textures.west = NULL;
	scene->textures.east = NULL;
	scene->colors.floor[0] = 0;
	scene->colors.floor[1] = 0;
	scene->colors.floor[2] = 0;
	scene->colors.ceiling[0] = 0;
	scene->colors.ceiling[1] = 0;
	scene->colors.ceiling[2] = 0;
	scene->colors.floor_color = -1;
	scene->colors.ceiling_color = -1;
	scene->map.grid = NULL;
	scene->map.width = 0;
	scene->map.height = 0;
	scene->map.player_x = 0;
	scene->map.player_y = 0;
	scene->map.player_dir = 'N';
}

t_scene	*init_scene(bool save_flag)
{
	t_scene	*scene;

	scene = (t_scene *)ft_calloc(1, sizeof(t_scene));
	if (!scene)
		print_error_ctx("Error: Memory allocation failed for t_scene", NULL,
			NULL);
	if (save_flag)
		scene->save_bmp = 1;
	else
		scene->save_bmp = 0;
	init_scene_defaults(scene);
	return (scene);
}
