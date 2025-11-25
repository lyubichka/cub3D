/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 01:46:00 by haiqbal           #+#    #+#             */
/*   Updated: 2025/11/26 01:44:45 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	rotate_left(t_cub3d *cub, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub->scene.player.dir_x;
	cub->scene.player.dir_x = cub->scene.player.dir_x * cos(rot_speed)
		- cub->scene.player.dir_y * sin(rot_speed);
	cub->scene.player.dir_y = old_dir_x * sin(rot_speed)
		+ cub->scene.player.dir_y * cos(rot_speed);
	old_plane_x = cub->scene.player.plane_x;
	cub->scene.player.plane_x = cub->scene.player.plane_x * cos(rot_speed)
		- cub->scene.player.plane_y * sin(rot_speed);
	cub->scene.player.plane_y = old_plane_x * sin(rot_speed)
		+ cub->scene.player.plane_y * cos(rot_speed);
}

void	rotate_right(t_cub3d *cub, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub->scene.player.dir_x;
	cub->scene.player.dir_x = cub->scene.player.dir_x * cos(-rot_speed)
		- cub->scene.player.dir_y * sin(-rot_speed);
	cub->scene.player.dir_y = old_dir_x * sin(-rot_speed)
		+ cub->scene.player.dir_y * cos(-rot_speed);
	old_plane_x = cub->scene.player.plane_x;
	cub->scene.player.plane_x = cub->scene.player.plane_x * cos(-rot_speed)
		- cub->scene.player.plane_y * sin(-rot_speed);
	cub->scene.player.plane_y = old_plane_x * sin(-rot_speed)
		+ cub->scene.player.plane_y * cos(-rot_speed);
}
