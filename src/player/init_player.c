/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 19:22:43 by haiqbal           #+#    #+#             */
/*   Updated: 2025/11/06 19:27:52 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	set_dir_plane(t_scene *scene, char dir)
{
	if (dir == 'N')
	{
		scene->player.dir_x = 0;
		scene->player.dir_y = -1;
		scene->player.plane_x = 0.66;
		scene->player.plane_y = 0;
	}
	else if (dir == 'S')
	{
		scene->player.dir_x = 0;
		scene->player.dir_y = 1;
		scene->player.plane_x = -0.66;
		scene->player.plane_y = 0;
	}
	else if (dir == 'E')
	{
		scene->player.dir_x = 1;
		scene->player.dir_y = 0;
		scene->player.plane_x = 0;
		scene->player.plane_y = 0.66;
	}
	else if (dir == 'W')
	{
		scene->player.dir_x = -1;
		scene->player.dir_y = 0;
		scene->player.plane_x = 0;
		scene->player.plane_y = -0.66;
	}
}

void	init_player(t_scene *scene)
{
	scene->player.pos_x = scene->map.player_x + 0.5;
	scene->player.pos_y = scene->map.player_y + 0.5;

	set_dir_plane(scene, scene->map.player_dir);
}
